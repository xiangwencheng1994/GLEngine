/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeColor.h
 * date: 2018/12/04
 * author: xiang
 *
 * License
 *
 * Copyright (c) 2017-2019, Xiang Wencheng <xiangwencheng@outlook.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the names of its contributors may be used to endorse or
 *   promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SGE_COLOR_H
#define SGE_COLOR_H

#include <core/sgePlatform.h>

namespace sge
{
    /**
     * Make a int color from a rgba data
     */
    inline int  INT_RGBA(byte r, byte g, byte b, byte a) { return ((int)r) << 24 + ((int)g) << 16 + ((int)b) << 8 + (int)a; }

    /**
     * Make a int color from a rgb data
     */
    inline int  INT_RGB(byte r, byte g, byte b) { return INT_RGBA(r, g, b, 255); }

    /**
     * Get the red channel from a int color
     */
    inline byte GET_RED(int color) { return (byte)((color & 0xFF000000) >> 24); }

    /**
     * Get the red channel from a int color
     */
    inline byte GET_GREEN(int color) { return (byte)((color & 0x00FF0000) >> 16); }

    /**
     * Get the blue channel from a int color
     */
    inline byte GET_BLUE(int color) { return (byte)((color & 0x0000FF00) >> 8); }

    /**
     * Get the alpha channel from a int color
     */
    inline byte GET_ALPHA(int color) { return (byte)color & 0x000000FF; }


    /**
     * Class for rgba color
     */
    class Rgba : public Vector4<uchar>
    {
    public:
        Rgba(uchar r, uchar g, uchar b, uchar a = 255)
            : Vector4(r, g, b, a)
        {}

        Rgba(int rgba)
            : Vector4(INT_RED(rgba),
                INT_GREEN(rgba),
                INT_BLUE(rgba),
                INT_ALPHA(rgba))
        {}

        Rgba(Vector4<float> color)
            : Vector4((uchar)(color.x * 255),
            (uchar)(color.y * 255),
                (uchar)(color.z * 255),
                (uchar)(color.w * 255))
        {}

        Rgba(Vector3<float> color)
            : Vector4((uchar)(color.x * 255),
            (uchar)(color.y * 255),
                (uchar)(color.z * 255),
                (uchar)(255))
        {}

        uchar red() const { return x; }
        uchar green() const { return y; }
        uchar blue() const { return z; }
        uchar alpha() const { return w; }
        int   value() const { return operator int(); }

        operator Vector4<float>() const { return Vector4<float>(x / 255.0f, y / 255.0f, z / 255.0f, w / 255.0f); }
        operator int() const { return INT_RGBA(red(), green(), blue(), alpha()); }
    };


    /**
     * Enumed Colors
     */
    enum    EnumColor
    {
        Snow = INT_RGB(255, 250, 250),
        PaleTurquoise1 = INT_RGB(187, 255, 255),
        GhostWhite = INT_RGB(248, 248, 255),
        PaleTurquoise2 = INT_RGB(174, 238, 238),
        WhiteSmoke = INT_RGB(245, 245, 245),
        PaleTurquoise3 = INT_RGB(150, 205, 205),
        Gainsboro = INT_RGB(220, 220, 220),
        PaleTurquoise4 = INT_RGB(102, 139, 139),
        FloralWhite = INT_RGB(255, 250, 240),
        CadetBlue1 = INT_RGB(152, 245, 255),
        OldLace = INT_RGB(253, 245, 230),
        CadetBlue2 = INT_RGB(142, 229, 238),
        Linen = INT_RGB(250, 240, 230),
        CadetBlue3 = INT_RGB(122, 197, 205),
        AntiqueWhite = INT_RGB(250, 235, 215),
        CadetBlue4 = INT_RGB(83, 134, 139),
        PapayaWhip = INT_RGB(255, 239, 213),
        Turquoise1 = INT_RGB(0, 245, 255),
        BlanchedAlmond = INT_RGB(255, 235, 205),
        Turquoise2 = INT_RGB(0, 229, 238),
        Bisque = INT_RGB(255, 228, 196),
        Turquoise3 = INT_RGB(0, 197, 205),
        PeachPuff = INT_RGB(255, 218, 185),
        Turquoise4 = INT_RGB(0, 134, 139),
        NavajoWhite = INT_RGB(255, 222, 173),
        Cyan1 = INT_RGB(0, 255, 255),
        Moccasin = INT_RGB(255, 228, 181),
        Cyan2 = INT_RGB(0, 238, 238),
        Cornsilk = INT_RGB(255, 248, 220),
        Cyan3 = INT_RGB(0, 205, 205),
        Ivory = INT_RGB(255, 255, 240),
        Cyan4 = INT_RGB(0, 139, 139),
        LemonChiffon = INT_RGB(255, 250, 205),
        DarkSlateGray1 = INT_RGB(151, 255, 255),
        Seashell = INT_RGB(255, 245, 238),
        DarkSlateGray2 = INT_RGB(141, 238, 238),
        Honeydew = INT_RGB(240, 255, 240),
        DarkSlateGray3 = INT_RGB(121, 205, 205),
        MintCream = INT_RGB(245, 255, 250),
        DarkSlateGray4 = INT_RGB(82, 139, 139),
        Azure = INT_RGB(240, 255, 255),
        Aquamarine1 = INT_RGB(127, 255, 212),
        AliceBlue = INT_RGB(240, 248, 255),
        Aquamarine2 = INT_RGB(118, 238, 198),
        lavender = INT_RGB(230, 230, 250),
        Aquamarine3 = INT_RGB(102, 205, 170),
        LavenderBlush = INT_RGB(255, 240, 245),
        Aquamarine4 = INT_RGB(69, 139, 116),
        MistyRose = INT_RGB(255, 228, 225),
        DarkSeaGreen1 = INT_RGB(193, 255, 193),
        White = INT_RGB(255, 255, 255),
        DarkSeaGreen2 = INT_RGB(180, 238, 180),
        Black = INT_RGB(0, 0, 0),
        DarkSeaGreen3 = INT_RGB(155, 205, 155),
        DarkSlateGray = INT_RGB(47, 79, 79),
        DarkSeaGreen4 = INT_RGB(105, 139, 105),
        DimGrey = INT_RGB(105, 105, 105),
        SeaGreen1 = INT_RGB(84, 255, 159),
        SlateGrey = INT_RGB(112, 128, 144),
        SeaGreen2 = INT_RGB(78, 238, 148),
        LightSlateGray = INT_RGB(119, 136, 153),
        SeaGreen3 = INT_RGB(67, 205, 128),
        Grey = INT_RGB(190, 190, 190),
        SeaGreen4 = INT_RGB(46, 139, 87),
        LightGray = INT_RGB(211, 211, 211),
        PaleGreen1 = INT_RGB(154, 255, 154),
        MidnightBlue = INT_RGB(25, 25, 112),
        PaleGreen2 = INT_RGB(144, 238, 144),
        NavyBlue = INT_RGB(0, 0, 128),
        PaleGreen3 = INT_RGB(124, 205, 124),
        CornflowerBlue = INT_RGB(100, 149, 237),
        PaleGreen4 = INT_RGB(84, 139, 84),
        DarkSlateBlue = INT_RGB(72, 61, 139),
        SpringGreen1 = INT_RGB(0, 255, 127),
        SlateBlue = INT_RGB(106, 90, 205),
        SpringGreen2 = INT_RGB(0, 238, 118),
        MediumSlateBlue = INT_RGB(123, 104, 238),
        SpringGreen3 = INT_RGB(0, 205, 102),
        LightSlateBlue = INT_RGB(132, 112, 255),
        SpringGreen4 = INT_RGB(0, 139, 69),
        MediumBlue = INT_RGB(0, 0, 205),
        Green1 = INT_RGB(0, 255, 0),
        RoyalBlue = INT_RGB(65, 105, 225),
        Green2 = INT_RGB(0, 238, 0),
        Blue = INT_RGB(0, 0, 255),
        Green3 = INT_RGB(0, 205, 0),
        DodgerBlue = INT_RGB(30, 144, 255),
        Green4 = INT_RGB(0, 139, 0),
        DeepSkyBlue = INT_RGB(0, 191, 255),
        Chartreuse1 = INT_RGB(127, 255, 0),
        SkyBlue = INT_RGB(135, 206, 235),
        Chartreuse2 = INT_RGB(118, 238, 0),
        LightSkyBlue = INT_RGB(135, 206, 250),
        Chartreuse3 = INT_RGB(102, 205, 0),
        SteelBlue = INT_RGB(70, 130, 180),
        Chartreuse4 = INT_RGB(69, 139, 0),
        LightSteelBlue = INT_RGB(176, 196, 222),
        OliveDrab1 = INT_RGB(192, 255, 62),
        LightBlue = INT_RGB(173, 216, 230),
        OliveDrab2 = INT_RGB(179, 238, 58),
        PowderBlue = INT_RGB(176, 224, 230),
        OliveDrab3 = INT_RGB(154, 205, 50),
        PaleTurquoise = INT_RGB(175, 238, 238),
        OliveDrab4 = INT_RGB(105, 139, 34),
        DarkTurquoise = INT_RGB(0, 206, 209),
        DarkOliveGreen1 = INT_RGB(202, 255, 112),
        MediumTurquoise = INT_RGB(72, 209, 204),
        DarkOliveGreen2 = INT_RGB(188, 238, 104),
        Turquoise = INT_RGB(64, 224, 208),
        DarkOliveGreen3 = INT_RGB(162, 205, 90),
        Cyan = INT_RGB(0, 255, 255),
        DarkOliveGreen4 = INT_RGB(110, 139, 61),
        LightCyan = INT_RGB(224, 255, 255),
        Khaki1 = INT_RGB(255, 246, 143),
        CadetBlue = INT_RGB(95, 158, 160),
        Khaki2 = INT_RGB(238, 230, 133),
        MediumAquamarine = INT_RGB(102, 205, 170),
        Khaki3 = INT_RGB(205, 198, 115),
        Aquamarine = INT_RGB(127, 255, 212),
        Khaki4 = INT_RGB(139, 134, 78),
        DarkGreen = INT_RGB(0, 100, 0),
        LightGoldenrod1 = INT_RGB(255, 236, 139),
        DarkOliveGreen = INT_RGB(85, 107, 47),
        LightGoldenrod2 = INT_RGB(238, 220, 130),
        DarkSeaGreen = INT_RGB(143, 188, 143),
        LightGoldenrod3 = INT_RGB(205, 190, 112),
        SeaGreen = INT_RGB(46, 139, 87),
        LightGoldenrod4 = INT_RGB(139, 129, 76),
        MediumSeaGreen = INT_RGB(60, 179, 113),
        LightYellow1 = INT_RGB(255, 255, 224),
        LightSeaGreen = INT_RGB(32, 178, 170),
        LightYellow2 = INT_RGB(238, 238, 209),
        PaleGreen = INT_RGB(152, 251, 152),
        LightYellow3 = INT_RGB(205, 205, 180),
        SpringGreen = INT_RGB(0, 255, 127),
        LightYellow4 = INT_RGB(139, 139, 122),
        LawnGreen = INT_RGB(124, 252, 0),
        Yellow1 = INT_RGB(255, 255, 0),
        Green = INT_RGB(0, 255, 0),
        Yellow2 = INT_RGB(238, 238, 0),
        Chartreuse = INT_RGB(127, 255, 0),
        Yellow3 = INT_RGB(205, 205, 0),
        MedSpringGreen = INT_RGB(0, 250, 154),
        Yellow4 = INT_RGB(139, 139, 0),
        GreenYellow = INT_RGB(173, 255, 47),
        Gold1 = INT_RGB(255, 215, 0),
        LimeGreen = INT_RGB(50, 205, 50),
        Gold2 = INT_RGB(238, 201, 0),
        YellowGreen = INT_RGB(154, 205, 50),
        Gold3 = INT_RGB(205, 173, 0),
        ForestGreen = INT_RGB(34, 139, 34),
        Gold4 = INT_RGB(139, 117, 0),
        OliveDrab = INT_RGB(107, 142, 35),
        Goldenrod1 = INT_RGB(255, 193, 37),
        DarkKhaki = INT_RGB(189, 183, 107),
        Goldenrod2 = INT_RGB(238, 180, 34),
        PaleGoldenrod = INT_RGB(238, 232, 170),
        Goldenrod3 = INT_RGB(205, 155, 29),
        LtGoldenrodYello = INT_RGB(250, 250, 210),
        Goldenrod4 = INT_RGB(139, 105, 20),
        LightYellow = INT_RGB(255, 255, 224),
        DarkGoldenrod1 = INT_RGB(255, 185, 15),
        Yellow = INT_RGB(255, 255, 0),
        DarkGoldenrod2 = INT_RGB(238, 173, 14),
        Gold = INT_RGB(255, 215, 0),
        DarkGoldenrod3 = INT_RGB(205, 149, 12),
        LightGoldenrod = INT_RGB(238, 221, 130),
        DarkGoldenrod4 = INT_RGB(139, 101, 8),
        goldenrod = INT_RGB(218, 165, 32),
        RosyBrown1 = INT_RGB(255, 193, 193),
        DarkGoldenrod = INT_RGB(184, 134, 11),
        RosyBrown2 = INT_RGB(238, 180, 180),
        RosyBrown = INT_RGB(188, 143, 143),
        RosyBrown3 = INT_RGB(205, 155, 155),
        IndianRed = INT_RGB(205, 92, 92),
        RosyBrown4 = INT_RGB(139, 105, 105),
        SaddleBrown = INT_RGB(139, 69, 19),
        IndianRed1 = INT_RGB(255, 106, 106),
        Sienna = INT_RGB(160, 82, 45),
        IndianRed2 = INT_RGB(238, 99, 99),
        Peru = INT_RGB(205, 133, 63),
        IndianRed3 = INT_RGB(205, 85, 85),
        Burlywood = INT_RGB(222, 184, 135),
        IndianRed4 = INT_RGB(139, 58, 58),
        Beige = INT_RGB(245, 245, 220),
        Sienna1 = INT_RGB(255, 130, 71),
        Wheat = INT_RGB(245, 222, 179),
        Sienna2 = INT_RGB(238, 121, 66),
        SandyBrown = INT_RGB(244, 164, 96),
        Sienna3 = INT_RGB(205, 104, 57),
        Tan = INT_RGB(210, 180, 140),
        Sienna4 = INT_RGB(139, 71, 38),
        Chocolate = INT_RGB(210, 105, 30),
        Burlywood1 = INT_RGB(255, 211, 155),
        Firebrick = INT_RGB(178, 34, 34),
        Burlywood2 = INT_RGB(238, 197, 145),
        Brown = INT_RGB(165, 42, 42),
        Burlywood3 = INT_RGB(205, 170, 125),
        DarkSalmon = INT_RGB(233, 150, 122),
        Burlywood4 = INT_RGB(139, 115, 85),
        Salmon = INT_RGB(250, 128, 114),
        Wheat1 = INT_RGB(255, 231, 186),
        LightSalmon = INT_RGB(255, 160, 122),
        Wheat2 = INT_RGB(238, 216, 174),
        Orange = INT_RGB(255, 165, 0),
        Wheat3 = INT_RGB(205, 186, 150),
        DarkOrange = INT_RGB(255, 140, 0),
        Wheat4 = INT_RGB(139, 126, 102),
        Coral = INT_RGB(255, 127, 80),
        Tan1 = INT_RGB(255, 165, 79),
        LightCoral = INT_RGB(240, 128, 128),
        Tan2 = INT_RGB(238, 154, 73),
        Tomato = INT_RGB(255, 99, 71),
        Tan3 = INT_RGB(205, 133, 63),
        OrangeRed = INT_RGB(255, 69, 0),
        Tan4 = INT_RGB(139, 90, 43),
        Red = INT_RGB(255, 0, 0),
        Chocolate1 = INT_RGB(255, 127, 36),
        HotPink = INT_RGB(255, 105, 180),
        Chocolate2 = INT_RGB(238, 118, 33),
        DeepPink = INT_RGB(255, 20, 147),
        Chocolate3 = INT_RGB(205, 102, 29),
        Pink = INT_RGB(255, 192, 203),
        Chocolate4 = INT_RGB(139, 69, 19),
        LightPink = INT_RGB(255, 182, 193),
        Firebrick1 = INT_RGB(255, 48, 48),
        PaleVioletRed = INT_RGB(219, 112, 147),
        Firebrick2 = INT_RGB(238, 44, 44),
        Maroon = INT_RGB(176, 48, 96),
        Firebrick3 = INT_RGB(205, 38, 38),
        MediumVioletRed = INT_RGB(199, 21, 133),
        Firebrick4 = INT_RGB(139, 26, 26),
        VioletRed = INT_RGB(208, 32, 144),
        Brown1 = INT_RGB(255, 64, 64),
        Magenta = INT_RGB(255, 0, 255),
        Brown2 = INT_RGB(238, 59, 59),
        Violet = INT_RGB(238, 130, 238),
        Brown3 = INT_RGB(205, 51, 51),
        Plum = INT_RGB(221, 160, 221),
        Brown4 = INT_RGB(139, 35, 35),
        Orchid = INT_RGB(218, 112, 214),
        Salmon1 = INT_RGB(255, 140, 105),
        MediumOrchid = INT_RGB(186, 85, 211),
        Salmon2 = INT_RGB(238, 130, 98),
        DarkOrchid = INT_RGB(153, 50, 204),
        Salmon3 = INT_RGB(205, 112, 84),
        DarkViolet = INT_RGB(148, 0, 211),
        Salmon4 = INT_RGB(139, 76, 57),
        BlueViolet = INT_RGB(138, 43, 226),
        LightSalmon1 = INT_RGB(255, 160, 122),
        Purple = INT_RGB(160, 32, 240),
        LightSalmon2 = INT_RGB(238, 149, 114),
        MediumPurple = INT_RGB(147, 112, 219),
        LightSalmon3 = INT_RGB(205, 129, 98),
        Thistle = INT_RGB(216, 191, 216),
        LightSalmon4 = INT_RGB(139, 87, 66),
        Snow1 = INT_RGB(255, 250, 250),
        Orange1 = INT_RGB(255, 165, 0),
        Snow2 = INT_RGB(238, 233, 233),
        Orange2 = INT_RGB(238, 154, 0),
        Snow3 = INT_RGB(205, 201, 201),
        Orange3 = INT_RGB(205, 133, 0),
        Snow4 = INT_RGB(139, 137, 137),
        Orange4 = INT_RGB(139, 90, 0),
        Seashell1 = INT_RGB(255, 245, 238),
        DarkOrange1 = INT_RGB(255, 127, 0),
        Seashell2 = INT_RGB(238, 229, 222),
        DarkOrange2 = INT_RGB(238, 118, 0),
        Seashell3 = INT_RGB(205, 197, 191),
        DarkOrange3 = INT_RGB(205, 102, 0),
        Seashell4 = INT_RGB(139, 134, 130),
        DarkOrange4 = INT_RGB(139, 69, 0),
        AntiqueWhite1 = INT_RGB(255, 239, 219),
        Coral1 = INT_RGB(255, 114, 86),
        AntiqueWhite2 = INT_RGB(238, 223, 204),
        Coral2 = INT_RGB(238, 106, 80),
        AntiqueWhite3 = INT_RGB(205, 192, 176),
        Coral3 = INT_RGB(205, 91, 69),
        AntiqueWhite4 = INT_RGB(139, 131, 120),
        Coral4 = INT_RGB(139, 62, 47),
        Bisque1 = INT_RGB(255, 228, 196),
        Tomato1 = INT_RGB(255, 99, 71),
        Bisque2 = INT_RGB(238, 213, 183),
        Tomato2 = INT_RGB(238, 92, 66),
        Bisque3 = INT_RGB(205, 183, 158),
        Tomato3 = INT_RGB(205, 79, 57),
        Bisque4 = INT_RGB(139, 125, 107),
        Tomato4 = INT_RGB(139, 54, 38),
        PeachPuff1 = INT_RGB(255, 218, 185),
        OrangeRed1 = INT_RGB(255, 69, 0),
        PeachPuff2 = INT_RGB(238, 203, 173),
        OrangeRed2 = INT_RGB(238, 64, 0),
        PeachPuff3 = INT_RGB(205, 175, 149),
        OrangeRed3 = INT_RGB(205, 55, 0),
        PeachPuff4 = INT_RGB(139, 119, 101),
        OrangeRed4 = INT_RGB(139, 37, 0),
        NavajoWhite1 = INT_RGB(255, 222, 173),
        Red1 = INT_RGB(255, 0, 0),
        NavajoWhite2 = INT_RGB(238, 207, 161),
        Red2 = INT_RGB(238, 0, 0),
        NavajoWhite3 = INT_RGB(205, 179, 139),
        Red3 = INT_RGB(205, 0, 0),
        NavajoWhite4 = INT_RGB(139, 121, 94),
        Red4 = INT_RGB(139, 0, 0),
        LemonChiffon1 = INT_RGB(255, 250, 205),
        DeepPink1 = INT_RGB(255, 20, 147),
        LemonChiffon2 = INT_RGB(238, 233, 191),
        DeepPink2 = INT_RGB(238, 18, 137),
        LemonChiffon3 = INT_RGB(205, 201, 165),
        DeepPink3 = INT_RGB(205, 16, 118),
        LemonChiffon4 = INT_RGB(139, 137, 112),
        DeepPink4 = INT_RGB(139, 10, 80),
        Cornsilk1 = INT_RGB(255, 248, 220),
        HotPink1 = INT_RGB(255, 110, 180),
        Cornsilk2 = INT_RGB(238, 232, 205),
        HotPink2 = INT_RGB(238, 106, 167),
        Cornsilk3 = INT_RGB(205, 200, 177),
        HotPink3 = INT_RGB(205, 96, 144),
        Cornsilk4 = INT_RGB(139, 136, 120),
        HotPink4 = INT_RGB(139, 58, 98),
        Ivory1 = INT_RGB(255, 255, 240),
        Pink1 = INT_RGB(255, 181, 197),
        Ivory2 = INT_RGB(238, 238, 224),
        Pink2 = INT_RGB(238, 169, 184),
        Ivory3 = INT_RGB(205, 205, 193),
        Pink3 = INT_RGB(205, 145, 158),
        Ivory4 = INT_RGB(139, 139, 131),
        Pink4 = INT_RGB(139, 99, 108),
        Honeydew1 = INT_RGB(240, 255, 240),
        LightPink1 = INT_RGB(255, 174, 185),
        Honeydew2 = INT_RGB(224, 238, 224),
        LightPink2 = INT_RGB(238, 162, 173),
        Honeydew3 = INT_RGB(193, 205, 193),
        LightPink3 = INT_RGB(205, 140, 149),
        Honeydew4 = INT_RGB(131, 139, 131),
        LightPink4 = INT_RGB(139, 95, 101),
        LavenderBlush1 = INT_RGB(255, 240, 245),
        PaleVioletRed1 = INT_RGB(255, 130, 171),
        LavenderBlush2 = INT_RGB(238, 224, 229),
        PaleVioletRed2 = INT_RGB(238, 121, 159),
        LavenderBlush3 = INT_RGB(205, 193, 197),
        PaleVioletRed3 = INT_RGB(205, 104, 137),
        LavenderBlush4 = INT_RGB(139, 131, 134),
        PaleVioletRed4 = INT_RGB(139, 71, 93),
        MistyRose1 = INT_RGB(255, 228, 225),
        Maroon1 = INT_RGB(255, 52, 179),
        MistyRose2 = INT_RGB(238, 213, 210),
        Maroon2 = INT_RGB(238, 48, 167),
        MistyRose3 = INT_RGB(205, 183, 181),
        Maroon3 = INT_RGB(205, 41, 144),
        MistyRose4 = INT_RGB(139, 125, 123),
        Maroon4 = INT_RGB(139, 28, 98),
        Azure1 = INT_RGB(240, 255, 255),
        VioletRed1 = INT_RGB(255, 62, 150),
        Azure2 = INT_RGB(224, 238, 238),
        VioletRed2 = INT_RGB(238, 58, 140),
        Azure3 = INT_RGB(193, 205, 205),
        VioletRed3 = INT_RGB(205, 50, 120),
        Azure4 = INT_RGB(131, 139, 139),
        VioletRed4 = INT_RGB(139, 34, 82),
        SlateBlue1 = INT_RGB(131, 111, 255),
        Magenta1 = INT_RGB(255, 0, 255),
        SlateBlue2 = INT_RGB(122, 103, 238),
        Magenta2 = INT_RGB(238, 0, 238),
        SlateBlue3 = INT_RGB(105, 89, 205),
        Magenta3 = INT_RGB(205, 0, 205),
        SlateBlue4 = INT_RGB(71, 60, 139),
        Magenta4 = INT_RGB(139, 0, 139),
        RoyalBlue1 = INT_RGB(72, 118, 255),
        Orchid1 = INT_RGB(255, 131, 250),
        RoyalBlue2 = INT_RGB(67, 110, 238),
        Orchid2 = INT_RGB(238, 122, 233),
        RoyalBlue3 = INT_RGB(58, 95, 205),
        Orchid3 = INT_RGB(205, 105, 201),
        RoyalBlue4 = INT_RGB(39, 64, 139),
        Orchid4 = INT_RGB(139, 71, 137),
        Blue1 = INT_RGB(0, 0, 255),
        Plum1 = INT_RGB(255, 187, 255),
        Blue2 = INT_RGB(0, 0, 238),
        Plum2 = INT_RGB(238, 174, 238),
        Blue3 = INT_RGB(0, 0, 205),
        Plum3 = INT_RGB(205, 150, 205),
        Blue4 = INT_RGB(0, 0, 139),
        Plum4 = INT_RGB(139, 102, 139),
        DodgerBlue1 = INT_RGB(30, 144, 255),
        MediumOrchid1 = INT_RGB(224, 102, 255),
        DodgerBlue2 = INT_RGB(28, 134, 238),
        MediumOrchid2 = INT_RGB(209, 95, 238),
        DodgerBlue3 = INT_RGB(24, 116, 205),
        MediumOrchid3 = INT_RGB(180, 82, 205),
        DodgerBlue4 = INT_RGB(16, 78, 139),
        MediumOrchid4 = INT_RGB(122, 55, 139),
        SteelBlue1 = INT_RGB(99, 184, 255),
        DarkOrchid1 = INT_RGB(191, 62, 255),
        SteelBlue2 = INT_RGB(92, 172, 238),
        DarkOrchid2 = INT_RGB(178, 58, 238),
        SteelBlue3 = INT_RGB(79, 148, 205),
        DarkOrchid3 = INT_RGB(154, 50, 205),
        SteelBlue4 = INT_RGB(54, 100, 139),
        DarkOrchid4 = INT_RGB(104, 34, 139),
        DeepSkyBlue1 = INT_RGB(0, 191, 255),
        Purple1 = INT_RGB(155, 48, 255),
        DeepSkyBlue2 = INT_RGB(0, 178, 238),
        Purple2 = INT_RGB(145, 44, 238),
        DeepSkyBlue3 = INT_RGB(0, 154, 205),
        Purple3 = INT_RGB(125, 38, 205),
        DeepSkyBlue4 = INT_RGB(0, 104, 139),
        Purple4 = INT_RGB(85, 26, 139),
        SkyBlue1 = INT_RGB(135, 206, 255),
        MediumPurple1 = INT_RGB(171, 130, 255),
        SkyBlue2 = INT_RGB(126, 192, 238),
        MediumPurple2 = INT_RGB(159, 121, 238),
        SkyBlue3 = INT_RGB(108, 166, 205),
        MediumPurple3 = INT_RGB(137, 104, 205),
        SkyBlue4 = INT_RGB(74, 112, 139),
        MediumPurple4 = INT_RGB(93, 71, 139),
        LightSkyBlue1 = INT_RGB(176, 226, 255),
        Thistle1 = INT_RGB(255, 225, 255),
        LightSkyBlue2 = INT_RGB(164, 211, 238),
        Thistle2 = INT_RGB(238, 210, 238),
        LightSkyBlue3 = INT_RGB(141, 182, 205),
        Thistle3 = INT_RGB(205, 181, 205),
        LightSkyBlue4 = INT_RGB(96, 123, 139),
        Thistle4 = INT_RGB(139, 123, 139),
        SlateGray1 = INT_RGB(198, 226, 255),
        grey11 = INT_RGB(28, 28, 28),
        SlateGray2 = INT_RGB(185, 211, 238),
        grey21 = INT_RGB(54, 54, 54),
        SlateGray3 = INT_RGB(159, 182, 205),
        grey31 = INT_RGB(79, 79, 79),
        SlateGray4 = INT_RGB(108, 123, 139),
        grey41 = INT_RGB(105, 105, 105),
        LightSteelBlue1 = INT_RGB(202, 225, 255),
        grey51 = INT_RGB(130, 130, 130),
        LightSteelBlue2 = INT_RGB(188, 210, 238),
        grey61 = INT_RGB(156, 156, 156),
        LightSteelBlue3 = INT_RGB(162, 181, 205),
        grey71 = INT_RGB(181, 181, 181),
        LightSteelBlue4 = INT_RGB(110, 123, 139),
        gray81 = INT_RGB(207, 207, 207),
        LightBlue1 = INT_RGB(191, 239, 255),
        gray91 = INT_RGB(232, 232, 232),
        LightBlue2 = INT_RGB(178, 223, 238),
        DarkGrey = INT_RGB(169, 169, 169),
        LightBlue3 = INT_RGB(154, 192, 205),
        DarkBlue = INT_RGB(0, 0, 139),
        LightBlue4 = INT_RGB(104, 131, 139),
        DarkCyan = INT_RGB(0, 139, 139),
        LightCyan1 = INT_RGB(224, 255, 255),
        DarkMagenta = INT_RGB(139, 0, 139),
        LightCyan2 = INT_RGB(209, 238, 238),
        DarkRed = INT_RGB(139, 0, 0),
        LightCyan3 = INT_RGB(180, 205, 205),
        LightCyan4 = INT_RGB(122, 139, 139),
        LightGreen = INT_RGB(144, 238, 144),
    };

} // namespace sge

#endif // !SGE_COLOR_H
