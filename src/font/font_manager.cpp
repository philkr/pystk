//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2016 SuperTuxKart-Team
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

#include "font/font_manager.hpp"

#include "config/stk_config.hpp"
#include "io/file_manager.hpp"
#include "font/bold_face.hpp"
#include "font/digit_face.hpp"
#include "font/face_ttf.hpp"
#include "font/regular_face.hpp"
#include "utils/string_utils.hpp"

FontManager *font_manager = NULL;
// ----------------------------------------------------------------------------
/** Constructor. It will initialize the \ref m_ft_library.
 */
FontManager::FontManager()
{
#ifndef SERVER_ONLY
    m_has_color_emoji = false;
    m_ft_library = NULL;
    m_digit_face = NULL;
    m_shaping_dpi = 128;

    checkFTError(FT_Init_FreeType(&m_ft_library), "loading freetype library");
#endif
}   // FontManager

// ----------------------------------------------------------------------------
/** Destructor. Clears all fonts and related stuff.
 */
FontManager::~FontManager()
{
    for (unsigned int i = 0; i < m_fonts.size(); i++)
        delete m_fonts[i];
    m_fonts.clear();

#ifndef SERVER_ONLY
    for (unsigned int i = 0; i < m_faces.size(); i++)
        checkFTError(FT_Done_Face(m_faces[i]), "removing faces for shaping");
    if (m_digit_face != NULL)
        checkFTError(FT_Done_Face(m_digit_face), "removing digit face");
    checkFTError(FT_Done_FreeType(m_ft_library), "removing freetype library");
#endif
}   // ~FontManager

#ifndef SERVER_ONLY
// ----------------------------------------------------------------------------
/** Load all TTFs from a list to m_faces.
 *  \param ttf_list List of TTFs to be loaded.
 */
std::vector<FT_Face>
                 FontManager::loadTTF(const std::vector<std::string>& ttf_list)
{
    std::vector <FT_Face> ret;
    for (const std::string& font : ttf_list)
    {
        FT_Face face = NULL;
        const std::string loc = file_manager
            ->getAssetChecked(FileManager::TTF, font.c_str(), true);
        font_manager->checkFTError(FT_New_Face(
            m_ft_library, loc.c_str(), 0, &face), loc + " is loaded");
        ret.push_back(face);
    }
    return ret;
}   // loadTTF

// ============================================================================
namespace LineBreakingRules
{
    // Here a list of characters that don't start or end a line for
    // chinese/japanese/korean. Only commonly use and full width characters are
    // included. You should use full width characters when writing CJK,
    // like using "。"instead of a ".", you can add more characters if needed.
    // For full list please visit:
    // http://webapp.docx4java.org/OnlineDemo/ecma376/WordML/kinsoku.html
    bool noStartingLine(char32_t c)
    {
        switch (c)
        {
            // ’
            case 8217:
                return true;
            // ”
            case 8221:
                return true;
            // 々
            case 12293:
                return true;
            // 〉
            case 12297:
                return true;
            // 》
            case 12299:
                return true;
            // 」
            case 12301:
                return true;
            // ｝
            case 65373:
                return true;
            // 〕
            case 12309:
                return true;
            // ）
            case 65289:
                return true;
            // 』
            case 12303:
                return true;
            // 】
            case 12305:
                return true;
            // 〗
            case 12311:
                return true;
            // ！
            case 65281:
                return true;
            // ％
            case 65285:
                return true;
            // ？
            case 65311:
                return true;
            // ｀
            case 65344:
                return true;
            // ，
            case 65292:
                return true;
            // ：
            case 65306:
                return true;
            // ；
            case 65307:
                return true;
            // ．
            case 65294:
                return true;
            // 。
            case 12290:
                return true;
            // 、
            case 12289:
                return true;
            default:
                return false;
        }
    }   // noStartingLine
    //-------------------------------------------------------------------------
    bool noEndingLine(char32_t c)
    {
        switch (c)
        {
            // ‘
            case 8216:
                return true;
            // “
            case 8220:
                return true;
            // 〈
            case 12296:
                return true;
            // 《
            case 12298:
                return true;
            // 「
            case 12300:
                return true;
            // ｛
            case 65371:
                return true;
            // 〔
            case 12308:
                return true;
            // （
            case 65288:
                return true;
            // 『
            case 12302:
                return true;
            // 【
            case 12304:
                return true;
            // 〖
            case 12310:
                return true;
            default:
                return false;
        }
    }   // noEndingLine
    //-------------------------------------------------------------------------
    // Helper function
    bool breakable(char32_t c)
    {
        if ((c > 12287 && c < 40960) || // Common CJK words
            (c > 44031 && c < 55204)  || // Hangul
            (c > 63743 && c < 64256)  || // More Chinese
            c == 173 || c == 32 || // Soft hyphen and white space
            c == 47 || c == 92 || // Slash and blackslash
            c == 8203) // Zero-width space
            return true;
        return false;
    }   // breakable
    //-------------------------------------------------------------------------
    void insertBreakMark(const std::u32string& str, std::vector<bool>& result)
    {
        assert(str.size() == result.size());
        for (unsigned i = 0; i < result.size(); i++)
        {
            char32_t c = str[i];
            char32_t nextline_char = 20;
            if (i < result.size() - 1)
                nextline_char = str[i + 1];
            if (breakable(c) && !noEndingLine(c) &&
                !noStartingLine(nextline_char))
            {
                result[i] = true;
            }
        }
    }   // insertBreakMark
}   // namespace LineBreakingRules

// ----------------------------------------------------------------------------
/* Turn text into glyph layout for rendering by libraqm. */
void FontManager::shape(const std::u32string& text,
                        std::vector<irr::gui::GlyphLayout>& gls,
                        std::vector<std::u32string>* line_data)

{
    // m_faces can be empty in null device
    if (text.empty() || m_faces.empty())
        return;

    auto lines = StringUtils::split(text, U'\n');
    // If the text end with and newline, it will miss a newline height, so we
    // it back here
    if (text.back() == U'\n')
        lines.push_back(U"");

    for (unsigned l = 0; l < lines.size(); l++)
    {
        if (l != 0)
        {
            gui::GlyphLayout gl = { 0 };
            gl.flags = gui::GLF_NEWLINE;
            gls.push_back(gl);
        }

        std::u32string& str = lines[l];
        str.erase(std::remove(str.begin(), str.end(), U'\r'), str.end());
        str.erase(std::remove(str.begin(), str.end(), U'\t'), str.end());
        if (str.empty())
        {
            if (line_data)
                line_data->push_back(str);
            continue;
        }

        {
            Log::error("FontManager", "Failed to raqm_create.");
            gls.clear();
            if (line_data)
                line_data->clear();
            return;
        }
    }
}   // shape

// ----------------------------------------------------------------------------
/* Return the cached glyph layouts for writing, it will clear all layouts if
 * not in-game and when the cached sized exceed a certain number. */
std::vector<irr::gui::GlyphLayout>&
                   FontManager::getCachedLayouts(const irr::core::stringw& str)
{
    const size_t MAX_LAYOUTS = 600;
    if (m_cached_gls.size() > MAX_LAYOUTS)
    {
        Log::debug("FontManager",
            "Clearing cached glyph layouts because too many.");
        clearCachedLayouts();
    }
    return m_cached_gls[str];
}   // getCachedLayouts

// ----------------------------------------------------------------------------
/** Convert text to glyph layouts for fast rendering with caching enabled
 *  If line_data is not null, each broken line u32string will be saved and
 *  can be used for advanced glyph and text mapping, and cache will be
 *  disabled, no newline characters are allowed in text if line_data is not
 *  NULL.
 */
void FontManager::initGlyphLayouts(const core::stringw& text,
                                   std::vector<irr::gui::GlyphLayout>& gls,
                                   std::vector<std::u32string>* line_data)
{
    if (text.empty())
        return;

    if (line_data != NULL)
    {
        shape(StringUtils::wideToUtf32(text), gls, line_data);
        return;
    }

    auto& cached_gls = getCachedLayouts(text);
    if (cached_gls.empty())
        shape(StringUtils::wideToUtf32(text), cached_gls);
    gls = cached_gls;
}   // initGlyphLayouts

// ----------------------------------------------------------------------------
FT_Face FontManager::loadColorEmoji()
{
    if (stk_config->m_color_emoji_ttf.empty())
        return NULL;
    FT_Face face = NULL;
    const std::string loc = file_manager->getAssetChecked(FileManager::TTF,
        stk_config->m_color_emoji_ttf.c_str(), true);
    FT_Error err = FT_New_Face(m_ft_library, loc.c_str(), 0, &face);
    if (err > 0)
    {
        Log::error("FontManager", "Something wrong when loading color emoji! "
            "The error code was %d.", err);
        return NULL;
    }

    if (!FT_HAS_COLOR(face) || face->num_fixed_sizes == 0)
    {
        Log::error("FontManager", "Bad %s color emoji, ignored.",
            stk_config->m_color_emoji_ttf.c_str());
        checkFTError(FT_Done_Face(face), "removing faces for emoji");
        return NULL;
    }
    // Use the largest size available, it will be scaled to regular face ttf
    // when loading the glyph, so it can reduce the blurring effect
    m_shaping_dpi = face->available_sizes[face->num_fixed_sizes - 1].height;
    checkFTError(FT_Select_Size(face, face->num_fixed_sizes - 1),
        "setting color emoji size");
    m_has_color_emoji = true;
    return face;
}   // loadColorEmoji

#endif

// ----------------------------------------------------------------------------
/** Initialize all \ref FaceTTF and \ref FontWithFace members.
 */
void FontManager::loadFonts()
{
#ifndef SERVER_ONLY
    // First load the TTF files required by each font
    std::vector<FT_Face> normal_ttf = loadTTF(stk_config->m_normal_ttf);
    std::vector<FT_Face> bold_ttf = normal_ttf;
    {
        assert(!normal_ttf.empty());
        FT_Face color_emoji = loadColorEmoji();
        if (!normal_ttf.empty() && color_emoji != NULL)
        {
            // Put color emoji after 1st default font so can use it before wqy
            // font
            normal_ttf.insert(normal_ttf.begin() + 1, color_emoji);
            // We don't use color emoji in bold font
            bold_ttf.insert(bold_ttf.begin() + 1, NULL);
        }
        // We use 16bit face idx in GlyphLayout class
        if (normal_ttf.size() > 65535)
            normal_ttf.resize(65535);
        for (uint16_t i = 0; i < normal_ttf.size(); i++)
            m_ft_faces_to_index[normal_ttf[i]] = i;
    }

    std::vector<FT_Face> digit_ttf = loadTTF(stk_config->m_digit_ttf);
    if (!digit_ttf.empty())
        m_digit_face = digit_ttf.front();
#endif

    // Now load fonts with settings of ttf file
    unsigned int font_loaded = 0;
    RegularFace* regular = new RegularFace();
#ifndef SERVER_ONLY
    regular->getFaceTTF()->loadTTF(normal_ttf);
#endif
    regular->init();
    m_fonts.push_back(regular);
    m_font_type_map[std::type_index(typeid(RegularFace))] = font_loaded++;

    BoldFace* bold = new BoldFace();
#ifndef SERVER_ONLY
    bold->getFaceTTF()->loadTTF(bold_ttf);
#endif
    bold->init();
    m_fonts.push_back(bold);
    m_font_type_map[std::type_index(typeid(BoldFace))] = font_loaded++;

    DigitFace* digit = new DigitFace();
#ifndef SERVER_ONLY
    digit->getFaceTTF()->loadTTF(digit_ttf);
#endif
    digit->init();
    m_fonts.push_back(digit);
    m_font_type_map[std::type_index(typeid(DigitFace))] = font_loaded++;

#ifndef SERVER_ONLY
    m_faces.insert(m_faces.end(), normal_ttf.begin(), normal_ttf.end());
#endif
}   // loadFonts
// ---------------------------------------------------
