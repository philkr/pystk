//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006-2015 Joerg Henrichs
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "items/attachment.hpp"

#include <algorithm>
#include "config/stk_config.hpp"
#include "config/user_config.hpp"
#include "graphics/explosion.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/render_info.hpp"
#include "items/attachment_manager.hpp"
#include "items/item_manager.hpp"
#include "items/projectile_manager.hpp"
#include "items/swatter.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"
#include "karts/explosion_animation.hpp"
#include "karts/kart_properties.hpp"
#include "modes/world.hpp"

#include "physics/triangle_mesh.hpp"
#include "tracks/track.hpp"
#include "physics/triangle_mesh.hpp"
#include "tracks/track.hpp"
#include "utils/constants.hpp"
#include "utils/objecttype.h"

#include "irrMath.h"
#include <IAnimatedMeshSceneNode.h>

/** Initialises the attachment each kart has.
 */
Attachment::Attachment(AbstractKart* kart)
{
    m_type                 = ATTACH_NOTHING;
    m_ticks_left           = 0;
    m_plugin               = NULL;
    m_kart                 = kart;
    m_previous_owner       = NULL;
    m_initial_speed        = 0.0f;

    m_node = irr_driver->addAnimatedMesh(
        attachment_manager->getMesh(Attachment::ATTACH_BOMB), "bomb",
        NULL, std::make_shared<RenderInfo>(0.0f, true, newObjectId(OT_BOMB)));
#ifdef DEBUG
    std::string debug_name = kart->getIdent()+" (attachment)";
    m_node->setName(debug_name.c_str());
#endif
    m_node->setParent(m_kart->getNode());
    m_node->setVisible(false);
}   // Attachment

//-----------------------------------------------------------------------------
/** Removes the attachment object. It removes the scene node used to display
 *  the attachment, and stops any sfx from being played.
 */
Attachment::~Attachment()
{
    if(m_node)
        irr_driver->removeNode(m_node);
}   // ~Attachment

//-----------------------------------------------------------------------------
/** Sets the attachment a kart has. This will also handle animation to be
 *  played, e.g. when a swatter replaces a bomb.
 *  \param type The type of the new attachment.
 *  \param time How long this attachment should stay with the kart.
 *  \param current_kart The kart from which an attachment is transferred.
 *         This is currently used for the bomb (to avoid that a bomb
 *         can be passed back to the previous owner). NULL if a no
 *         previous owner exists.
 */
void Attachment::set(AttachmentType type, int ticks,
                     AbstractKart *current_kart,
                     bool set_by_rewind_parachute)
{
    bool was_bomb = m_type == ATTACH_BOMB;
    int16_t prev_ticks = m_ticks_left;
    clear();

    // If necessary create the appropriate plugin which encapsulates
    // the associated behavior
    switch(type)
    {
    case ATTACH_SWATTER:
        m_plugin =
            new Swatter(m_kart, was_bomb ? prev_ticks : -1, ticks, this);
        break;
    default:
        break;
    }   // switch(type)

    m_type             = type;
    m_ticks_left       = ticks;
    m_previous_owner   = current_kart;
    m_scaling_end_ticks = World::getWorld()->getTicksSinceStart() +
        stk_config->time2Ticks(0.7f);

    m_initial_speed = 0;
    // A parachute can be attached as result of the usage of an item. In this
    // case we have to save the current kart speed so that it can be detached
    // by slowing down.
    // if set by rewind the parachute ticks is already correct
    if (m_type == ATTACH_PARACHUTE && !set_by_rewind_parachute)
    {
        const KartProperties *kp = m_kart->getKartProperties();
        float speed_mult;

        float initial_speed = m_kart->getSpeed();
        // if going very slowly or backwards, braking won't remove parachute
        if(initial_speed <= 1.5f) initial_speed = 1.5f;

        float f = initial_speed / kp->getParachuteMaxSpeed();
        float temp_mult = kp->getParachuteDurationSpeedMult();

        // duration can't be reduced by higher speed
        if (temp_mult < 1.0f) temp_mult = 1.0f;

        if (f > 1.0f) f = 1.0f;   // cap fraction

        speed_mult = 1.0f + (f *  (temp_mult - 1.0f));

        m_ticks_left = int(m_ticks_left * speed_mult);
        int initial_speed_round = (int)(initial_speed * 100.0f);
        initial_speed_round =
            irr::core::clamp(initial_speed_round, -32768, 32767);
        m_initial_speed = (int16_t)initial_speed_round;
    }
}   // set

// -----------------------------------------------------------------------------
/** Removes any attachement currently on the kart. As for the anvil attachment,
 *  takes care of resetting the owner kart's physics structures to account for
 *  the updated mass.
 */
void Attachment::clear()
{
    if (m_plugin)
    {
        delete m_plugin;
        m_plugin = NULL;
    }

    m_type = ATTACH_NOTHING;
    m_ticks_left = 0;
    m_initial_speed = 0;
}   // clear

// -----------------------------------------------------------------------------
/** Selects the new attachment. In order to simplify synchronisation with the
 *  server, the new item is based on the current world time. 
 *  \param item The item that was collected.
 */
void Attachment::hitBanana(ItemState *item_state)
{
    //Bubble gum shield effect:
    if(m_type == ATTACH_BUBBLEGUM_SHIELD ||
       m_type == ATTACH_NOLOK_BUBBLEGUM_SHIELD)
    {
        m_ticks_left = 0;
        return;
    }

    int leftover_ticks = 0;

    bool add_a_new_item = true;

    if (race_manager->isBattleMode())
    {
        World::getWorld()->kartHit(m_kart->getWorldKartId());
        if (m_kart->getKartAnimation() == NULL)
            ExplosionAnimation::create(m_kart);
        return;
    }

    AttachmentType new_attachment = ATTACH_NOTHING;
    const KartProperties *kp = m_kart->getKartProperties();
    // Use this as a basic random number to make sync with server easier.
    // Divide by 16 to increase probablity to have same time as server in
    // case of a few physics frames different between client and server.
    int ticks = World::getWorld()->getTicksSinceStart() / 16;
    switch(getType())   // If there already is an attachment, make it worse :)
    {
    case ATTACH_BOMB:
        {
        add_a_new_item = false;
        {
            HitEffect* he = new Explosion(m_kart->getXYZ(), "explosion_bomb.xml");
            projectile_manager->addHitEffect(he);
        }
        if (m_kart->getKartAnimation() == NULL)
            ExplosionAnimation::create(m_kart);
        clear();
        new_attachment = AttachmentType(ticks % 3);
        // Disable the banana on which the kart just is for more than the
        // default time. This is necessary to avoid that a kart lands on the
        // same banana again once the explosion animation is finished, giving
        // the kart the same penalty twice.
        int ticks = 
            std::max(item_state->getTicksTillReturn(), 
                     stk_config->time2Ticks(kp->getExplosionDuration() + 2.0f));
        item_state->setTicksTillReturn(ticks);
        break;
        }
    case ATTACH_ANVIL:
        // if the kart already has an anvil, attach a new anvil,
        // and increase the overall time
        new_attachment = ATTACH_ANVIL;
        leftover_ticks  = m_ticks_left;
        break;
    case ATTACH_PARACHUTE:
        new_attachment = ATTACH_PARACHUTE;
        leftover_ticks  = m_ticks_left;
        break;
    default:
        if (race_manager->getMinorMode() == RaceManager::MINOR_MODE_TIME_TRIAL)
            new_attachment = AttachmentType(ticks % 2);
        else
            new_attachment = AttachmentType(ticks % 3);
    }   // switch

    if (add_a_new_item)
    {
        switch (new_attachment)
        {
        case ATTACH_PARACHUTE:
        {
            set(ATTACH_PARACHUTE, kp->getParachuteDuration() + leftover_ticks);
            int initial_speed_round = (int)(m_kart->getSpeed() * 100.0f);
            initial_speed_round =
                irr::core::clamp(initial_speed_round, -32768, 32767);
            m_initial_speed = (int16_t)initial_speed_round;
            // if going very slowly or backwards,
            // braking won't remove parachute
            if (m_initial_speed <= 150) m_initial_speed = 150;
            break;
        }
        case ATTACH_ANVIL:
            set(ATTACH_ANVIL, stk_config->time2Ticks(kp->getAnvilDuration())
                + leftover_ticks                                      );
            // Reduce speed once (see description above), all other changes are
            // handled in Kart::updatePhysics
            m_kart->adjustSpeed(kp->getAnvilSpeedFactor());
            break;
        case ATTACH_BOMB:
            set( ATTACH_BOMB, stk_config->time2Ticks(stk_config->m_bomb_time)
                            + leftover_ticks                                 );
            break;
        default:
            break;
        }   // switch
    }
}   // hitBanana

//-----------------------------------------------------------------------------
/** Updates the attachments in case of a kart-kart collision. This must only
 *  be called for one of the karts in the collision, since it will update
 *  the attachment for both karts.
 *  \param other Pointer to the other kart hit.
 */
void Attachment::handleCollisionWithKart(AbstractKart *other)
{
    Attachment *attachment_other=other->getAttachment();

    if(getType()==Attachment::ATTACH_BOMB)
    {
        // Don't attach a bomb when the kart is shielded
        if(other->isShielded())
        {
            other->decreaseShieldTime();
            return;
        }
        // If both karts have a bomb, explode them immediately:
        if(attachment_other->getType()==Attachment::ATTACH_BOMB)
        {
            setTicksLeft(0);
            attachment_other->setTicksLeft(0);
        }
        else  // only this kart has a bomb, move it to the other
        {
            // if there are only two karts, let them switch bomb from one to other
            if (getPreviousOwner() != other ||
                World::getWorld()->getNumKarts() <= 2)
            {
                // Don't move if this bomb was from other kart originally
                other->getAttachment()
                    ->set(ATTACH_BOMB, 
                          getTicksLeft()+stk_config->time2Ticks(
                                           stk_config->m_bomb_time_increase),
                          m_kart);
                clear();
            }
        }
    }   // type==BOMB
    else if(attachment_other->getType()==Attachment::ATTACH_BOMB &&
             (attachment_other->getPreviousOwner()!=m_kart || 
               World::getWorld()->getNumKarts() <= 2         )      )
    {
        // Don't attach a bomb when the kart is shielded
        if(m_kart->isShielded())
        {
            m_kart->decreaseShieldTime();
            return;
        }
        set(ATTACH_BOMB,
            other->getAttachment()->getTicksLeft()+
               stk_config->time2Ticks(stk_config->m_bomb_time_increase),
            other);
        other->getAttachment()->clear();
    }
    else
    {
    }

}   // handleCollisionWithKart

//-----------------------------------------------------------------------------
void Attachment::update(int ticks)
{
    if(m_type==ATTACH_NOTHING) return;

    // suspend the bomb during animations to avoid having 2 animations at the
    // same time should the bomb explode before the previous animation is done
    if (m_type == ATTACH_BOMB && m_kart->getKartAnimation() != NULL)
        return;

    m_ticks_left -= ticks;

    if (m_plugin)
    {
        if (m_plugin->updateAndTestFinished(ticks))
        {
            clear();  // also removes the plugin
            return;
        }
    }

    switch (m_type)
    {
    case ATTACH_PARACHUTE:
        {
        // Partly handled in Kart::updatePhysics
        // Otherwise: disable if a certain percantage of
        // initial speed was lost
        // This percentage is based on the ratio of
        // initial_speed / initial_max_speed

        const KartProperties *kp = m_kart->getKartProperties();

        float initial_speed = (float)m_initial_speed / 100.f;
        float f = initial_speed / kp->getParachuteMaxSpeed();
        if (f > 1.0f) f = 1.0f;   // cap fraction
        if (m_kart->getSpeed() <= initial_speed *
                                 (kp->getParachuteLboundFraction() +
                                  f * (kp->getParachuteUboundFraction()
                                     - kp->getParachuteLboundFraction())))
        {
            m_ticks_left = -1;
        }
        }
        break;
    case ATTACH_ANVIL:     // handled in Kart::updatePhysics
    case ATTACH_NOTHING:   // Nothing to do, but complete all cases for switch
    case ATTACH_MAX:
        m_initial_speed = 0;
        break;
    case ATTACH_SWATTER:
        // Everything is done in the plugin.
        m_initial_speed = 0;
        break;
    case ATTACH_NOLOKS_SWATTER:
    case ATTACH_SWATTER_ANIM:
        // Should never be called, these symbols are only used as an index for
        // the model, Nolok's attachment type is ATTACH_SWATTER
        assert(false);
        break;
    case ATTACH_BOMB:
    {
        m_initial_speed = 0;
        if (m_ticks_left <= 0)
        {
            {
                HitEffect* he = new Explosion(m_kart->getXYZ(), "explosion_bomb.xml");
                projectile_manager->addHitEffect(he);
            }
            if (m_kart->getKartAnimation() == NULL)
                ExplosionAnimation::create(m_kart);
        }
        break;
    }
    case ATTACH_BUBBLEGUM_SHIELD:
    case ATTACH_NOLOK_BUBBLEGUM_SHIELD:
        m_initial_speed = 0;
        if (m_ticks_left <= 0)
        {
            ItemManager::get()->dropNewItem(Item::ITEM_BUBBLEGUM, m_kart);
        }
        break;
    }   // switch

    // Detach attachment if its time is up.
    if (m_ticks_left <= 0)
        clear();
}   // update

// ----------------------------------------------------------------------------
void Attachment::updateGraphics(float dt)
{
    // Add the suitable graphical effects if different attachment is set
    if (m_type != m_graphical_type)
    {
        // Attachement is different, reset and add suitable sfx effects
        m_node->setPosition(core::vector3df(0.0f, 0.0f, 0.0f));
        m_node->setRotation(core::vector3df(0.0f, 0.0f, 0.0f));
        m_node->setScale(core::vector3df(1.0f, 1.0f, 1.0f));
        m_node->setLoopMode(true);
        switch (m_type)
        {
        case ATTACH_NOTHING:
            break;
        case ATTACH_SWATTER:
            // Graphical model set in swatter class
            break;
        default:
            m_node->setMesh(attachment_manager->getMesh(m_type));
            break;
        }   // switch(type)

        if (m_type != ATTACH_NOTHING)
        {
            m_node->setAnimationSpeed(0);
            m_node->setCurrentFrame(0);
        }
        if (UserConfigParams::m_particles_effects > 1 &&
            m_type == ATTACH_PARACHUTE)
        {
            // .blend was created @25 (<10 real, slow computer), make it faster
            m_node->setAnimationSpeed(50);
        }
        m_graphical_type = m_type;
    }

    if (m_plugin)
        m_plugin->updateGraphics(dt);

    if (m_type != ATTACH_NOTHING)
    {
        m_node->setVisible(true);
        bool is_shield = m_type == ATTACH_BUBBLEGUM_SHIELD ||
                        m_type == ATTACH_NOLOK_BUBBLEGUM_SHIELD;
        float wanted_node_scale = is_shield ?
            std::max(1.0f, m_kart->getHighestPoint() * 1.1f) : 1.0f;
        float scale_ratio = stk_config->ticks2Time(m_scaling_end_ticks -
            World::getWorld()->getTicksSinceStart()) / 0.7f;
        if (scale_ratio > 0.0f)
        {
            float scale = 0.3f * scale_ratio +
                wanted_node_scale * (1.0f - scale_ratio);
            m_node->setScale(core::vector3df(scale, scale, scale));
        }
        else
        {
            m_node->setScale(core::vector3df(
                wanted_node_scale, wanted_node_scale, wanted_node_scale));
        }
        int slow_flashes = stk_config->time2Ticks(3.0f);
        if (is_shield && m_ticks_left < slow_flashes)
        {
            // Bubble gum flashing when close to dropping
            int ticks_per_flash = stk_config->time2Ticks(0.2f);

            int fast_flashes = stk_config->time2Ticks(0.5f);
            if (m_ticks_left < fast_flashes)
            {
                ticks_per_flash = stk_config->time2Ticks(0.07f);
            }

            int division = (m_ticks_left / ticks_per_flash);
            m_node->setVisible((division & 0x1) == 0);
        }
    }
    else
        m_node->setVisible(false);

    switch (m_type)
    {
    case ATTACH_BOMB:
    {
        // Mesh animation frames are 1 to 61 frames (60 steps)
        // The idea is change second by second, counterclockwise 60 to 0 secs
        // If longer times needed, it should be a surprise "oh! bomb activated!"
        float time_left = stk_config->ticks2Time(m_ticks_left);
        if (time_left <= (m_node->getEndFrame() - m_node->getStartFrame() - 1))
        {
            m_node->setCurrentFrame(m_node->getEndFrame()
                - m_node->getStartFrame() - 1 - time_left);
        }
        return;
    }
    default:
        break;
    }   // switch
}   // updateGraphics

// ----------------------------------------------------------------------------
/** Return the additional weight of the attachment (some attachments slow
 *  karts down by also making them heavier).
 */
float Attachment::weightAdjust() const
{
    return m_type == ATTACH_ANVIL 
           ? m_kart->getKartProperties()->getAnvilWeight() 
          : 0.0f;
}   // weightAdjust
