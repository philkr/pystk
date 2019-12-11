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

#include "items/powerup.hpp"

#include "config/stk_config.hpp"
#include "items/attachment.hpp"
#include "items/item_manager.hpp"
#include "items/projectile_manager.hpp"
#include "items/rubber_ball.hpp"
#include "karts/abstract_kart.hpp"
#include "karts/controller/controller.hpp"
#include "karts/kart_properties.hpp"
#include "modes/world.hpp"

#include "physics/triangle_mesh.hpp"
#include "tracks/track.hpp"
#include "utils/string_utils.hpp"
#include "utils/log.hpp" //TODO: remove after debugging is done

//-----------------------------------------------------------------------------
/** Constructor, stores the kart to which this powerup belongs.
 *  \param kart The kart to which this powerup belongs.
 */
Powerup::Powerup(AbstractKart* kart)
{
    m_kart      = kart;
    reset();
}   // Powerup

//-----------------------------------------------------------------------------
/** Frees the memory for the sound effects.
 */
Powerup::~Powerup()
{
}   // ~Powerup

//-----------------------------------------------------------------------------
/** Resets the powerup, called at begin of a race.
 */
void Powerup::reset()
{
    m_type = PowerupManager::POWERUP_NOTHING;
    m_number = 0;

    int type, number;
    World::getWorld()->getDefaultCollectibles( &type, &number );
    set( (PowerupManager::PowerupType)type, number );
}   // reset

//-----------------------------------------------------------------------------
void Powerup::update(int ticks)
{
}   // update

//-----------------------------------------------------------------------------
/** Sets the collected items. The number of items is increased if the same
 *  item is currently collected, otherwise replaces the existing item. It also
 *  sets item specific sounds.
 *  \param type Thew new type.
 *  \param n Number of items of the given type.
 */
void Powerup::set(PowerupManager::PowerupType type, int n)
{
    if (m_type==type)
    {
        m_number+=n;
        // Limit to 255 (save space in network state saving)
        if(m_number>255) m_number = 255;
        return;
    }
    m_type=type;

    // Limit to 255 (save space in network state saving)
    if(n>255) n = 255;

    m_number=n;
}  // set

//-----------------------------------------------------------------------------
/** Returns the icon for the currently collected powerup. Used in the
 *  race_gui to display the collected item.
 */
Material *Powerup::getIcon() const
{
    // Check if it's one of the types which have a separate
    // data file which includes the icon:
    return powerup_manager->getIcon(m_type);
}   // getIcon

//-----------------------------------------------------------------------------
/** Use (fire) this powerup.
 */
void Powerup::use()
{
    const KartProperties *kp = m_kart->getKartProperties();

    m_number--;
    World *world = World::getWorld();
    switch (m_type)
    {
    case PowerupManager::POWERUP_ZIPPER:
        m_kart->handleZipper(NULL);
        break ;
    case PowerupManager::POWERUP_SWITCH:
        {
            ItemManager::get()->switchItems();
            break;
        }
    case PowerupManager::POWERUP_CAKE:
    case PowerupManager::POWERUP_RUBBERBALL:
    case PowerupManager::POWERUP_BOWLING:
    case PowerupManager::POWERUP_PLUNGER:
        if(stk_config->m_shield_restrict_weapons)
            m_kart->setShieldTime(0.0f); // make weapon usage destroy the shield
        projectile_manager->newProjectile(m_kart, m_type);
        break ;

    case PowerupManager::POWERUP_SWATTER:
        m_kart->getAttachment()
                ->set(Attachment::ATTACH_SWATTER,
                      stk_config->time2Ticks(kp->getSwatterDuration()));
        break;

    case PowerupManager::POWERUP_BUBBLEGUM:
        // use the bubble gum the traditional way, if the kart is looking back
        if (m_kart->getControls().getLookBack())
        {
            Item *new_item = 
                ItemManager::get()->dropNewItem(Item::ITEM_BUBBLEGUM, m_kart);

            // E.g. ground not found in raycast.
            if(!new_item) return;
        }
        else // if the kart is looking forward, use the bubblegum as a shield
        {

            if(!m_kart->isShielded()) //if the previous shield had been used up.
            {
                if (m_kart->getIdent() == "nolok")
                {
                    m_kart->getAttachment()
                          ->set(Attachment::ATTACH_NOLOK_BUBBLEGUM_SHIELD,
                                stk_config->
                                  time2Ticks(kp->getBubblegumShieldDuration()));
                }
                else
                {
                    m_kart->getAttachment()
                          ->set(Attachment::ATTACH_BUBBLEGUM_SHIELD,
                                stk_config->
                                  time2Ticks(kp->getBubblegumShieldDuration()));
                }
            }
            else // using a bubble gum while still having a shield
            {
                if (m_kart->getIdent() == "nolok")
                {
                    m_kart->getAttachment()
                          ->set(Attachment::ATTACH_NOLOK_BUBBLEGUM_SHIELD,
                                stk_config->
                                 time2Ticks(kp->getBubblegumShieldDuration()));
                }
                else
                {
                    m_kart->getAttachment()
                          ->set(Attachment::ATTACH_BUBBLEGUM_SHIELD,
                                stk_config->
                                time2Ticks(kp->getBubblegumShieldDuration()
                                           + m_kart->getShieldTime()       ) );
                }
            }

        }   // end of PowerupManager::POWERUP_BUBBLEGUM
        break;

    case PowerupManager::POWERUP_ANVIL:
        //Attach an anvil(twice as good as the one given
        //by the bananas) to the kart in the 1st position.
        for(unsigned int i = 0 ; i < world->getNumKarts(); ++i)
        {
            AbstractKart *kart=world->getKart(i);
            if(kart->isEliminated() || kart->isInvulnerable()) continue;
            if(kart == m_kart) continue;
            if(kart->getPosition() == 1)
            {
                kart->getAttachment()->set(Attachment::ATTACH_ANVIL,
                                           stk_config->
                                           time2Ticks(kp->getAnvilDuration()) );
                kart->adjustSpeed(kp->getAnvilSpeedFactor() * 0.5f);

                break;
            }
        }

        break;

    case PowerupManager::POWERUP_PARACHUTE:
        {
            AbstractKart* player_kart = NULL;
            //Attach a parachute(that last 1,3 time as long as the
            //one from the bananas and is affected by the rank multiplier)
            //to all the karts that are in front of this one.
            for(unsigned int i = 0 ; i < world->getNumKarts(); ++i)
            {
                AbstractKart *kart=world->getKart(i);
                if(kart->isEliminated() || kart== m_kart || kart->isInvulnerable()) continue;
                if(kart->isShielded())
                {
                    kart->decreaseShieldTime();
                    continue;
                }
                if(m_kart->getPosition() > kart->getPosition())
                {
                    float rank_mult, position_factor;
                    //0 if the one before the item user ; 1 if first ; scaled inbetween
                    if (kart->getPosition() == 1)
                    {
                        position_factor = 1.0f;
                    }
                    else //m_kart position is always >= 3
                    {
                        float rank_factor;

                        rank_factor = (float)(kart->getPosition()   - 1) 
                                    / (float)(m_kart->getPosition() - 2);
                        position_factor = 1.0f - rank_factor;
                    }

                    rank_mult = 1 + (position_factor * 
                                     (kp->getParachuteDurationRankMult() - 1));

                    kart->getAttachment()
                        ->set(Attachment::ATTACH_PARACHUTE,
                              int(kp->getParachuteDurationOther()*rank_mult) );

                    if(kart->getController()->isLocalPlayerController())
                        player_kart = kart;
                }
            }
        }
        break;

    case PowerupManager::POWERUP_NOTHING:
        {
            if(!m_kart->getKartAnimation())
                m_kart->beep();
        }
        break;
    default : break;
    }

    if ( m_number <= 0 )
    {
        m_number = 0;
        m_type   = PowerupManager::POWERUP_NOTHING;
    }
}   // use

//-----------------------------------------------------------------------------
/** This function is called when a bnous box is it. This function can be
 *  called on a server (in which case item and add_info are not used),
 *  or on a client, in which case the item and additional info is used
 *  to make sure server and clients are synched correctly.
 *  \param n
 *  \param item_state The item_state (bonux box) that was hit. This is
 *         necessary for servers so that the clients can be informed which
 *         item was collected.
 */
void Powerup::hitBonusBox(const ItemState &item_state)
{
    // Position can be -1 in case of a battle mode (which doesn't have
    // positions), but this case is properly handled in getRandomPowerup.
    int position = m_kart->getPosition();

    unsigned int n=1;
    PowerupManager::PowerupType new_powerup;
    World *world = World::getWorld();

    // Determine a 'random' number based on time, index of the item,
    // and position of the kart. The idea is that this process is
    // randomly enough to get the right distribution of the powerups,
    // does not involve additional network communication to keep 
    // client and server in sync, and is not exploitable:
    // While it is not possible for a client to determine the item
    // (the server will always finally determine which item a player
    // receives), we need to make sure that people cannot modify the
    // sources and display the item that will be collected next
    // at a box - otherwise the player could chose the 'best' box.
    // Using synchronised pseudo-random-generators would not prevent
    // cheating, since the a cheater could determine the next random
    // number that will be used. If we use the server to always
    // send the information to the clients, we need to add a delay
    // before items can be used.
    // So instead we determine a random number that is based on:
    // (1) The item id
    // (2) The time
    // (3) The position of the kart
    // (4) An extra random 64bit integer
    // Using (1) means that not all boxes at a certain time for a kart
    // will give the same box. Using (2) means that the item will
    // change over time - even if the next item is displayed, it 
    // will mean a cheater has to wait, and because of the frequency
    // of the time component it will also be difficult to get the
    // item at the right time. Using (3) adds another cheat-prevention
    // layer: even if a cheater is waiting for the right sequence
    // of items, if he is overtaken the sequence will change, using (4)
    // to avoid same item sequence when starting
    //
    // In order to increase the probability of correct client prediction
    // in networking (where there might be 1 or 2 frames difference
    // between client and server when collecting an item), the time
    // is divided by 10, meaning even if there is one frame difference,
    // the client will still have a 90% chance to correctly predict the
    // item. We multiply the item with a 'large' (more or less random)
    // number to spread the random values across the (typically 200)
    // weights used in the PowerupManager - same for the position.
    uint64_t random_number = item_state.getItemId() * 31 +
        world->getTicksSinceStart() / 10 + position * 23 +
        powerup_manager->getRandomSeed();

    // Use this random number as a seed of a PRNG (based on the one in 
    // bullet's btSequentialImpulseConstraintSolver) to avoid getting
    // consecutive numbers. Without this the same item could be 
    // produced for a longer period of time, which would make this
    // exploitable: someone could hack STK to display the item that
    // can be collected for each box, and the pick the one with the
    // 'best' item.
    random_number = (1664525L * random_number + 1013904223L);
    // Lower bits only have a short period, so mix in higher
    // bits:
    random_number ^= (random_number >> 16);
    random_number ^= (random_number >> 8);

    new_powerup = powerup_manager->getRandomPowerup(position, &n, 
                                                    random_number);

    // Always add a new powerup in ITEM_MODE_NEW (or if the kart
    // doesn't have a powerup atm).
    if(m_type == PowerupManager::POWERUP_NOTHING ||
       stk_config->m_same_powerup_mode == STKConfig::POWERUP_MODE_NEW )
    {
        set( new_powerup, n );
    }
    else
    {
        // If powerup mode is 'SAME', or it's ONLY_IF_SAME and it is the
        // same powerup, increase the number of items.
        if(stk_config->m_same_powerup_mode == STKConfig::POWERUP_MODE_SAME ||
            new_powerup==m_type)
        {
            m_number+=n;
            if(m_number > MAX_POWERUPS)
                m_number = MAX_POWERUPS;
        }
    }
    // Ignore new powerup if it is different from the current one and not
    // POWERUP_MODE_SAME

}   // hitBonusBox
