/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeGUIRenderer.cpp
 * date: 2018/12/09
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

#include <core/sgeGUIRenderer.h>

#ifdef USE_NVG_GL3
    #ifdef OPENGLES
        #define NANOVG_GLES3_IMPLEMENTATION
    #else
        #define NANOVG_GL3_IMPLEMENTATION
    #endif
#else
    #ifdef OPENGLES
        #define NANOVG_GLES2_IMPLEMENTATION
    #else
        #define NANOVG_GL3_IMPLEMENTATION
    #endif
#endif

#include "../nanovg/nanovg.h"
#include "../nanovg/nanovg_gl.h"

namespace sge
{
    GUIImage::GUIImage(GUIRenderer* renderer, int imageId)
        : _renderer(renderer)
        , _imageId(imageId)
    {}

    GUIImage::~GUIImage()
    {
        if (_renderer && _imageId >= 0)
        {
            nvgDeleteImage((NVGcontext*)_renderer->_nativeCtx, _imageId);
            _imageId    =   -1;
        }
    }

    inline int2 GUIImage::getImageSize()
    {
        int2    size;
        nvgImageSize((NVGcontext*)_renderer->_nativeCtx, _imageId, &size.x, &size.y);
        return  size;
    }

    GUIRenderer::GUIRenderer()
        : _nativeCtx(NULL)
    {
        int flag    =   NVG_ANTIALIAS | NVG_STENCIL_STROKES;
#ifdef _DEBUG
        flag    |=  NVG_DEBUG;
#endif
#if defined NANOVG_GL2
        _nativeCtx  =   nvgCreateGL2(flag);
#elif defined NANOVG_GL3
        _nativeCtx  =   nvgCreateGL3(flag);
#elif defined NANOVG_GLES2
        _nativeCtx  =   nvgCreateGLES2(flag);
#elif defined NANOVG_GLES3
        _nativeCtx  =   nvgCreateGLES3(flag);
#endif
        ASSERT((NVGcontext*)_nativeCtx);
    }

    GUIRenderer::~GUIRenderer()
    {
        if (_nativeCtx)
        {
#if defined NANOVG_GL2
            nvgDeleteGL2((NVGcontext*)_nativeCtx);
#elif defined NANOVG_GL3
            nvgDeleteGL3((NVGcontext*)_nativeCtx);
#elif defined NANOVG_GLES2
            nvgDeleteGLES2((NVGcontext*)_nativeCtx);
#elif defined NANOVG_GLES3
            nvgDeleteGLES3((NVGcontext*)_nativeCtx);
#endif
            _nativeCtx  =   NULL;
        }
    }

    inline int GUIRenderer::save()
    {
        return  nvgSave((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::restore(int index)
    {
        nvgRestore((NVGcontext*)_nativeCtx, index);
    }

    inline void GUIRenderer::reset()
    {
        nvgReset((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::setShapeAntiAlias(bool enable)
    {
        nvgShapeAntiAlias((NVGcontext*)_nativeCtx, enable ? 1 : 0);
    }

    inline void GUIRenderer::setStrokeColor(float r, float g, float b, float a)
    {
        nvgStrokeColor((NVGcontext*)_nativeCtx, nvgRGBAf(r, g, b, a));
    }

    inline void GUIRenderer::setStrokePaint(const GUIPaint& paint)
    {
        nvgStrokePaint((NVGcontext*)_nativeCtx, *(NVGpaint*)&paint);
    }

    inline void GUIRenderer::setFillColor(float r, float g, float b, float a)
    {
        nvgFillColor((NVGcontext*)_nativeCtx, nvgRGBAf(r, g, b, a));
    }

    inline void GUIRenderer::setFillColor(const vec4f& color)
    {
        nvgFillColor((NVGcontext*)_nativeCtx, *(NVGcolor*)&color);
    }

    inline void GUIRenderer::setFillPaint(const GUIPaint& paint)
    {
        nvgFillPaint((NVGcontext*)_nativeCtx, *(NVGpaint*)&paint);
    }

    inline void GUIRenderer::setMiterLimit(float limit)
    {
        nvgMiterLimit((NVGcontext*)_nativeCtx, limit);
    }

    inline void GUIRenderer::setStrokeWidth(float size)
    {
        nvgStrokeWidth((NVGcontext*)_nativeCtx, size);
    }

    inline void GUIRenderer::setLineCap(GUILineCapType type)
    {
        nvgLineCap((NVGcontext*)_nativeCtx, type);
    }

    inline void GUIRenderer::setLineJoin(GUILineJoinType type)
    {
        nvgLineJoin((NVGcontext*)_nativeCtx, type);
    }

    inline void GUIRenderer::globalAlpha(float alpha)
    {
        nvgGlobalAlpha((NVGcontext*)_nativeCtx, alpha);
    }

    inline void GUIRenderer::resetTransform()
    {
        nvgResetTransform((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::doTransform(const float* xform)
    {
        nvgTransform((NVGcontext*)_nativeCtx, xform[0], xform[1], xform[2], xform[3], xform[4], xform[5]);
    }

    inline void GUIRenderer::getCurrentTransform(float * out_xform)
    {
        nvgCurrentTransform((NVGcontext*)_nativeCtx, out_xform);
    }

    inline void GUIRenderer::doTranslate(float x, float y)
    {
        nvgTranslate((NVGcontext*)_nativeCtx, x, y);
    }

    inline void GUIRenderer::doRotate(float angle)
    {
        nvgRotate((NVGcontext*)_nativeCtx, DEG2RAD(angle));
    }

    inline void GUIRenderer::doSkewX(float angle)
    {
        nvgSkewX((NVGcontext*)_nativeCtx, DEG2RAD(angle));
    }

    inline void GUIRenderer::doSkewY(float angle)
    {
        nvgSkewY((NVGcontext*)_nativeCtx, DEG2RAD(angle));
    }

    inline void GUIRenderer::doScale(float x, float y)
    {
        nvgScale((NVGcontext*)_nativeCtx, x, y);
    }

    inline GUIImage GUIRenderer::loadImage(const char* filename, int imageFlag)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImage((NVGcontext*)_nativeCtx, filename, imageFlag);
        return GUIImage(this, imageId);
    }

    inline GUIImage GUIRenderer::loadImage(const byte* fileData, size_t dataLen, int imageFlag)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImageMem((NVGcontext*)_nativeCtx, imageFlag, fileData, dataLen);
        return GUIImage(this, imageId);
    }

    inline GUIImage GUIRenderer::loadImage(const byte* rgbaData, int w, int h, int imageFlags)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImageRGBA((NVGcontext*)_nativeCtx, w, h, imageFlags, rgbaData);
        return GUIImage(this, imageId);
    }
    
    GUIPaint GUIRenderer::createLinearGradient(float sx, float sy, float ex, float ey,
        const vec4f& icol, const vec4f& ocol)
    {
        GUIPaint paint;
        *(NVGpaint*)&paint = nvgLinearGradient((NVGcontext*)_nativeCtx, sx, sy, ex, ey, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }

    GUIPaint GUIRenderer::createBoxGradient(float x, float y, float w, float h, float r, float f,
        const vec4f& icol, const vec4f& ocol)
    {
        GUIPaint paint;
        *(NVGpaint*)&paint = nvgBoxGradient((NVGcontext*)_nativeCtx, x, y, w, h, r, f, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }

    GUIPaint GUIRenderer::createRadialGradient(float cx, float cy, float inr, float outr,
        const vec4f& icol, const vec4f& ocol)
    {
        GUIPaint paint;
        *(NVGpaint*)&paint = nvgRadialGradient((NVGcontext*)_nativeCtx, cx, cy, inr, outr, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }

    GUIPaint GUIRenderer::createImagePattern(float ox, float oy, float ex, float ey,
        float angle, int image, float alpha)
    {
        GUIPaint paint;
        *(NVGpaint*)&paint = nvgImagePattern((NVGcontext*)_nativeCtx, ox, oy, ex, ey, angle, image, alpha);
        return paint;
    }
    
    inline void GUIRenderer::addScissor(float x, float y, float w, float h)
    {
        nvgScissor((NVGcontext*)_nativeCtx, x, y, w, h);
    }

    inline void GUIRenderer::addIntersectScissor(float x, float y, float w, float h)
    {
        nvgIntersectScissor((NVGcontext*)_nativeCtx, x, y, w, h);
    }

    inline void GUIRenderer::resetScissor()
    {
        nvgResetScissor((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::beginFrame(float w, float h, float dpi)
    {
        nvgBeginFrame((NVGcontext*)_nativeCtx, w, h, dpi);
    }

    void GUIRenderer::endFrame()
    {
        nvgEndFrame((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::cancelFrame()
    {
        nvgCancelFrame((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::beginPath()
    {
        nvgBeginPath((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::moveTo(float x, float y)
    {
        nvgMoveTo((NVGcontext*)_nativeCtx, x, y);
    }

    inline void GUIRenderer::lineTo(float x, float y)
    {
        nvgLineTo((NVGcontext*)_nativeCtx, x, y);
    }

    inline void GUIRenderer::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y)
    {
        nvgBezierTo((NVGcontext*)_nativeCtx, c1x, c1y, c2x, c2y, x, y);
    }

    inline void GUIRenderer::quadTo(float c1x, float c1y, float x, float y)
    {
        nvgQuadTo((NVGcontext*)_nativeCtx, c1x, c1y, x, y);
    }

    inline void GUIRenderer::arcTo(float x1, float y1, float x2, float y2, float radius)
    {
        nvgArcTo((NVGcontext*)_nativeCtx, x1, y1, x2, y2, radius);
    }

    inline void GUIRenderer::closePath()
    {
        nvgClosePath((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::pathWinding(bool solid)
    {
        nvgPathWinding((NVGcontext*)_nativeCtx, solid ? NVG_SOLID : NVG_HOLE);
    }

    inline void GUIRenderer::arc(float centerX, float centerY, float radius, float startAngle, float endAngle, bool ccw)
    {
        nvgArc((NVGcontext*)_nativeCtx, centerX, centerY, radius, startAngle, endAngle, ccw ? NVG_CCW : NVG_CW);
    }

    inline void GUIRenderer::rect(float x, float y, float w, float h)
    {
        nvgRect((NVGcontext*)_nativeCtx, x, y, w, h);
    }

    inline void GUIRenderer::roundedRect(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
    {
        nvgRoundedRectVarying((NVGcontext*)_nativeCtx, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft);
    }

    inline void GUIRenderer::ellipse(float cx, float cy, float rx, float ry)
    {
        nvgEllipse((NVGcontext*)_nativeCtx, cx, cy, rx, ry);
    }

    inline void GUIRenderer::circle(float cx, float cy, float radius)
    {
        nvgCircle((NVGcontext*)_nativeCtx, cx, cy, radius);
    }

    inline void GUIRenderer::fillPath()
    {
        nvgFill((NVGcontext*)_nativeCtx);
    }

    inline void GUIRenderer::strokePath()
    {
        nvgStroke((NVGcontext*)_nativeCtx);
    }
    
    inline int GUIRenderer::loadFont(const char* name, const char* filename)
    {
        return nvgCreateFont((NVGcontext*)_nativeCtx, name, filename);
    }

    inline int GUIRenderer::loadFontMem(const char* name, unsigned char* data, int ndata, int freeData)
    {
        return nvgCreateFontMem((NVGcontext*)_nativeCtx, name, data, ndata, freeData);
    }
    
    inline int GUIRenderer::findFont(const char* name)
    {
        return nvgFindFont((NVGcontext*)_nativeCtx, name);
    }

    inline int GUIRenderer::addFallbackFontId(int baseFont, int fallbackFont)
    {
        return nvgAddFallbackFontId((NVGcontext*)_nativeCtx, baseFont, fallbackFont);
    }

    inline int GUIRenderer::addFallbackFont(const char* baseFont, const char* fallbackFont)
    {
        return nvgAddFallbackFont((NVGcontext*)_nativeCtx, baseFont, fallbackFont);
    }

    inline void GUIRenderer::setFontSize(float size)
    {
        nvgFontSize((NVGcontext*)_nativeCtx, size);
    }

    inline void GUIRenderer::setFontBlur(float blur)
    {
        nvgFontBlur((NVGcontext*)_nativeCtx, blur);
    }

    inline void GUIRenderer::setTextLetterSpacing(float spacing)
    {
        nvgTextLetterSpacing((NVGcontext*)_nativeCtx, spacing);
    }

    inline void GUIRenderer::setTextLineHeight(float lineHeight)
    {
        nvgTextLineHeight((NVGcontext*)_nativeCtx, lineHeight);
    }

    inline void GUIRenderer::setTextAlign(GUIAlignment align)
    {
        nvgTextAlign((NVGcontext*)_nativeCtx, align);
    }

    inline void GUIRenderer::setFont(int font)
    {
        nvgFontFaceId((NVGcontext*)_nativeCtx, font);
    }

    inline void GUIRenderer::setFont(const char* font)
    {
        nvgFontFace((NVGcontext*)_nativeCtx, font);
    }
    
    inline float GUIRenderer::drawText(float x, float y, const char* string, const char* end)
    {
        return nvgText((NVGcontext*)_nativeCtx, x, y, string, end);
    }

    inline void GUIRenderer::drawTextBox(float x, float y, float breakRowWidth, const char* string, const char* end)
    {
        nvgTextBox((NVGcontext*)_nativeCtx, x, y, breakRowWidth, string, end);
    }

    inline float GUIRenderer::measureText(float x, float y, const char* string, const char* end, float* bounds)
    {
        return nvgTextBounds((NVGcontext*)_nativeCtx, x, y, string, end, bounds);
    }

    inline void GUIRenderer::measureTextBox(float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds)
    {
        nvgTextBoxBounds((NVGcontext*)_nativeCtx, x, y, breakRowWidth, string, end, bounds);
    }

    //void GUIRenderer::textGlyphPositions(float x, float y, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions);

    inline void GUIRenderer::getTextMetrics(float* ascender, float* descender, float* lineh)
    {
        nvgTextMetrics((NVGcontext*)_nativeCtx, ascender, descender, lineh);
    }
    
    //void GUIRenderer::textBreakLines(const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows);

}