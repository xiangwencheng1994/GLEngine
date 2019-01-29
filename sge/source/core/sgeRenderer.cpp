#include <core/sgeRenderer.h>
#include <core/sgeGLContext.h>

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
    RendererImage::RendererImage(Renderer* renderer, int imageId)
        : mRenderer(renderer)
        , mImageId(imageId)
    {}

    RendererImage::~RendererImage()
    {
        if (mRenderer && mImageId >= 0)
        {
            nvgDeleteImage((NVGcontext*)mRenderer->mNativeCtx, mImageId);
            mImageId = -1;
        }
    }

    inline int2 RendererImage::getImageSize()
    {
        int2 size;
        nvgImageSize((NVGcontext*)mRenderer->mNativeCtx, mImageId, &size.x, &size.y);
        return size;
    }

    inline RendererPaint::RendererPaint() {}

    Renderer::Renderer()
        : mNativeCtx(NULL)
    {
        int flag = NVG_ANTIALIAS | NVG_STENCIL_STROKES;
#ifdef _DEBUG
        flag |= NVG_DEBUG;
#endif
#if defined NANOVG_GL2
        mNativeCtx = nvgCreateGL2(flag);
#elif defined NANOVG_GL3
        mNativeCtx = nvgCreateGL3(flag);
#elif defined NANOVG_GLES2
        mNativeCtx = nvgCreateGLES2(flag);
#elif defined NANOVG_GLES3
        mNativeCtx = nvgCreateGLES3(flag);
#endif
        ASSERT((NVGcontext*)mNativeCtx);
    }

    Renderer::~Renderer()
    {
        if (mNativeCtx)
        {
#if defined NANOVG_GL2
            nvgDeleteGL2((NVGcontext*)mNativeCtx);
#elif defined NANOVG_GL3
            nvgDeleteGL3((NVGcontext*)mNativeCtx);
#elif defined NANOVG_GLES2
            nvgDeleteGLES2((NVGcontext*)mNativeCtx);
#elif defined NANOVG_GLES3
            nvgDeleteGLES3((NVGcontext*)mNativeCtx);
#endif
            mNativeCtx = NULL;
        }
    }

    inline int Renderer::save()
    {
        return nvgSave((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::restore(int index)
    {
        nvgRestore((NVGcontext*)mNativeCtx, index);
    }

    inline void Renderer::reset()
    {
        nvgReset((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::setShapeAntiAlias(bool enable)
    {
        nvgShapeAntiAlias((NVGcontext*)mNativeCtx, enable ? 1 : 0);
    }

    inline void Renderer::setStrokeColor(float r, float g, float b, float a)
    {
        nvgStrokeColor((NVGcontext*)mNativeCtx, nvgRGBAf(r, g, b, a));
    }

    inline void Renderer::setStrokePaint(const RendererPaint& paint)
    {
        nvgStrokePaint((NVGcontext*)mNativeCtx, *(NVGpaint*)&paint);
    }

    inline void Renderer::setFillColor(float r, float g, float b, float a)
    {
        nvgFillColor((NVGcontext*)mNativeCtx, nvgRGBAf(r, g, b, a));
    }

    inline void Renderer::setFillColor(const float4& color)
    {
        nvgFillColor((NVGcontext*)mNativeCtx, *(NVGcolor*)&color);
    }

    inline void Renderer::setFillPaint(const RendererPaint& paint)
    {
        nvgFillPaint((NVGcontext*)mNativeCtx, *(NVGpaint*)&paint);
    }

    inline void Renderer::setMiterLimit(float limit)
    {
        nvgMiterLimit((NVGcontext*)mNativeCtx, limit);
    }

    inline void Renderer::setStrokeWidth(float size)
    {
        nvgStrokeWidth((NVGcontext*)mNativeCtx, size);
    }

    inline void Renderer::setLineCap(LineCapType type)
    {
        nvgLineCap((NVGcontext*)mNativeCtx, type);
    }

    inline void Renderer::setLineJoin(LineJoinType type)
    {
        nvgLineJoin((NVGcontext*)mNativeCtx, type);
    }

    inline void Renderer::globalAlpha(float alpha)
    {
        nvgGlobalAlpha((NVGcontext*)mNativeCtx, alpha);
    }

    inline void Renderer::resetTransform()
    {
        nvgResetTransform((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::doTransform(const float* xform)
    {
        nvgTransform((NVGcontext*)mNativeCtx, xform[0], xform[1], xform[2], xform[3], xform[4], xform[5]);
    }

    inline void Renderer::getCurrentTransform(float * out_xform)
    {
        nvgCurrentTransform((NVGcontext*)mNativeCtx, out_xform);
    }

    inline void Renderer::doTranslate(float x, float y)
    {
        nvgTranslate((NVGcontext*)mNativeCtx, x, y);
    }

    inline void Renderer::doRotate(float angle)
    {
        nvgRotate((NVGcontext*)mNativeCtx, DEG2RAD(angle));
    }

    inline void Renderer::doSkewX(float angle)
    {
        nvgSkewX((NVGcontext*)mNativeCtx, DEG2RAD(angle));
    }

    inline void Renderer::doSkewY(float angle)
    {
        nvgSkewY((NVGcontext*)mNativeCtx, DEG2RAD(angle));
    }

    inline void Renderer::doScale(float x, float y)
    {
        nvgScale((NVGcontext*)mNativeCtx, x, y);
    }


    inline RendererImage Renderer::loadImage(const char* file, int imageFlag)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImage((NVGcontext*)mNativeCtx, file, imageFlag);
        return RendererImage(this, imageId);
    }


    inline RendererImage Renderer::loadImage(byte* fileData, size_t dataLen, int imageFlag)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImageMem((NVGcontext*)mNativeCtx, imageFlag, fileData, dataLen);
        return RendererImage(this, imageId);
    }

    inline RendererImage Renderer::loadImage(const byte* rgbaData, int w, int h, int imageFlags)
    {
        //TODO: return RefPtr if found in cache map
        int imageId = nvgCreateImageRGBA((NVGcontext*)mNativeCtx, w, h, imageFlags, rgbaData);
        return RendererImage(this, imageId);
    }
    
    RendererPaint Renderer::createLinearGradient(float sx, float sy, float ex, float ey,
        const float4& icol, const float4& ocol)
    {
        RendererPaint paint;
        *(NVGpaint*)&paint = nvgLinearGradient((NVGcontext*)mNativeCtx, sx, sy, ex, ey, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }

    RendererPaint Renderer::createBoxGradient(float x, float y, float w, float h, float r, float f,
        const float4& icol, const float4& ocol)
    {
        RendererPaint paint;
        *(NVGpaint*)&paint = nvgBoxGradient((NVGcontext*)mNativeCtx, x, y, w, h, r, f, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }


    RendererPaint Renderer::createRadialGradient(float cx, float cy, float inr, float outr,
        const float4& icol, const float4& ocol)
    {
        RendererPaint paint;
        *(NVGpaint*)&paint = nvgRadialGradient((NVGcontext*)mNativeCtx, cx, cy, inr, outr, *(NVGcolor*)(&icol), *(NVGcolor*)(&ocol));
        return paint;
    }
    

    RendererPaint Renderer::createImagePattern(float ox, float oy, float ex, float ey,
        float angle, int image, float alpha)
    {
        RendererPaint paint;
        *(NVGpaint*)&paint = nvgImagePattern((NVGcontext*)mNativeCtx, ox, oy, ex, ey, angle, image, alpha);
        return paint;
    }
    
    inline void Renderer::addScissor(float x, float y, float w, float h)
    {
        nvgScissor((NVGcontext*)mNativeCtx, x, y, w, h);
    }

    inline void Renderer::addIntersectScissor(float x, float y, float w, float h)
    {
        nvgIntersectScissor((NVGcontext*)mNativeCtx, x, y, w, h);
    }

    inline void Renderer::resetScissor()
    {
        nvgResetScissor((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::beginFrame(float w, float h, float dpi)
    {
        nvgBeginFrame((NVGcontext*)mNativeCtx, w, h, dpi);
    }

    void Renderer::endFrame()
    {
        nvgEndFrame((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::cancelFrame()
    {
        nvgCancelFrame((NVGcontext*)mNativeCtx);
    }


    inline void Renderer::beginPath()
    {
        nvgBeginPath((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::moveTo(float x, float y)
    {
        nvgMoveTo((NVGcontext*)mNativeCtx, x, y);
    }

    inline void Renderer::lineTo(float x, float y)
    {
        nvgLineTo((NVGcontext*)mNativeCtx, x, y);
    }

    inline void Renderer::bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y)
    {
        nvgBezierTo((NVGcontext*)mNativeCtx, c1x, c1y, c2x, c2y, x, y);
    }

    inline void Renderer::quadTo(float c1x, float c1y, float x, float y)
    {
        nvgQuadTo((NVGcontext*)mNativeCtx, c1x, c1y, x, y);
    }

    inline void Renderer::arcTo(float x1, float y1, float x2, float y2, float radius)
    {
        nvgArcTo((NVGcontext*)mNativeCtx, x1, y1, x2, y2, radius);
    }

    inline void Renderer::closePath()
    {
        nvgClosePath((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::pathWinding(bool solid)
    {
        nvgPathWinding((NVGcontext*)mNativeCtx, solid ? NVG_SOLID : NVG_HOLE);
    }

    inline void Renderer::arc(float centerX, float centerY, float radius, float startAngle, float endAngle, bool ccw)
    {
        nvgArc((NVGcontext*)mNativeCtx, centerX, centerY, radius, startAngle, endAngle, ccw ? NVG_CCW : NVG_CW);
    }

    inline void Renderer::rect(float x, float y, float w, float h)
    {
        nvgRect((NVGcontext*)mNativeCtx, x, y, w, h);
    }

    inline void Renderer::roundedRect(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
    {
        nvgRoundedRectVarying((NVGcontext*)mNativeCtx, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft);
    }

    inline void Renderer::ellipse(float cx, float cy, float rx, float ry)
    {
        nvgEllipse((NVGcontext*)mNativeCtx, cx, cy, rx, ry);
    }

    inline void Renderer::circle(float cx, float cy, float radius)
    {
        nvgCircle((NVGcontext*)mNativeCtx, cx, cy, radius);
    }

    inline void Renderer::fillPath()
    {
        nvgFill((NVGcontext*)mNativeCtx);
    }

    inline void Renderer::strokePath()
    {
        nvgStroke((NVGcontext*)mNativeCtx);
    }
    
    inline int Renderer::loadFont(const char* name, const char* filename)
    {
        return nvgCreateFont((NVGcontext*)mNativeCtx, name, filename);
    }

    inline int Renderer::loadFontMem(const char* name, unsigned char* data, int ndata, int freeData)
    {
        return nvgCreateFontMem((NVGcontext*)mNativeCtx, name, data, ndata, freeData);
    }
    
    inline int Renderer::findFont(const char* name)
    {
        return nvgFindFont((NVGcontext*)mNativeCtx, name);
    }

    inline int Renderer::addFallbackFontId(int baseFont, int fallbackFont)
    {
        return nvgAddFallbackFontId((NVGcontext*)mNativeCtx, baseFont, fallbackFont);
    }

    inline int Renderer::addFallbackFont(const char* baseFont, const char* fallbackFont)
    {
        return nvgAddFallbackFont((NVGcontext*)mNativeCtx, baseFont, fallbackFont);
    }

    inline void Renderer::setFontSize(float size)
    {
        nvgFontSize((NVGcontext*)mNativeCtx, size);
    }

    inline void Renderer::setFontBlur(float blur)
    {
        nvgFontBlur((NVGcontext*)mNativeCtx, blur);
    }

    inline void Renderer::setTextLetterSpacing(float spacing)
    {
        nvgTextLetterSpacing((NVGcontext*)mNativeCtx, spacing);
    }

    inline void Renderer::setTextLineHeight(float lineHeight)
    {
        nvgTextLineHeight((NVGcontext*)mNativeCtx, lineHeight);
    }

    inline void Renderer::setTextAlign(Alignment align)
    {
        nvgTextAlign((NVGcontext*)mNativeCtx, align);
    }

    inline void Renderer::setFont(int font)
    {
        nvgFontFaceId((NVGcontext*)mNativeCtx, font);
    }

    inline void Renderer::setFont(const char* font)
    {
        nvgFontFace((NVGcontext*)mNativeCtx, font);
    }
    
    inline float Renderer::drawText(float x, float y, const char* string, const char* end)
    {
        return nvgText((NVGcontext*)mNativeCtx, x, y, string, end);
    }

    inline void Renderer::drawTextBox(float x, float y, float breakRowWidth, const char* string, const char* end)
    {
        nvgTextBox((NVGcontext*)mNativeCtx, x, y, breakRowWidth, string, end);
    }

    inline int Renderer::getTextBoxLineCount(const char* string, const char* end, float breakRowWidth, RendererTextRow* rows, int maxRows)
    {
        return nvgTextBreakLines((NVGcontext*)mNativeCtx, string, end,
            breakRowWidth, (NVGtextRow*)rows, maxRows);
    }

    inline float Renderer::measureText(float x, float y, const char* string, const char* end, float* bounds)
    {
        return nvgTextBounds((NVGcontext*)mNativeCtx, x, y, string, end, bounds);
    }

    inline void Renderer::measureTextBox(float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds)
    {
        nvgTextBoxBounds((NVGcontext*)mNativeCtx, x, y, breakRowWidth, string, end, bounds);
    }

    //void Renderer::textGlyphPositions(float x, float y, const char* string, const char* end, NVGglyphPosition* positions, int maxPositions);

    inline void Renderer::getTextMetrics(float* ascender, float* descender, float* lineh)
    {
        nvgTextMetrics((NVGcontext*)mNativeCtx, ascender, descender, lineh);
    }
    
    //void Renderer::textBreakLines(const char* string, const char* end, float breakRowWidth, NVGtextRow* rows, int maxRows);

}