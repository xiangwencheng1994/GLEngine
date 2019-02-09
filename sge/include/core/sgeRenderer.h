/**
 *
 * Simple graphic engine
 * "sge" libraiy is a simple graphics engine, named sge.
 *
 * sgeRenderer.h
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

#ifndef SGE_RENDERER_H
#define SGE_RENDERER_H

#include <core/sgePlatform.h>
#include <core/sgeMath.h>
#include <core/sgeRefPtr.h>

namespace sge
{
    /**
     * Enum of line cap types
     */
    typedef enum LineCapType {
        LineCapButt     = 0,
        LineCapRound    = 1,
        LineCapSquare   = 2,
    } LineCapType;


    /**
     * Enum of line join type
     */
    typedef enum LineJoinType {
        LineJoinRound   = 1,
        LineJoinBevel   = 3,
        LineJoinMiter   = 4,
    } LineJoinType;
    

    /**
     * Enum of image flags for renderer
     */
    typedef enum ImageFlag {
        GenerateMipmaps = 1 << 0, // Generate mipmaps during creation of the image.
        RepeatX         = 1 << 1, // Repeat image in X direction.
        RepeatY         = 1 << 2, // Repeat image in Y direction.
        FlipyY          = 1 << 3, // Flips (inverses) image in Y direction when rendered.
        PreMultiplied   = 1 << 4, // Image data has premultiplied alpha.
        Nearest         = 1 << 5, // Image interpolation is Nearest instead Linear
    } ImageFlag;


    /**
     * Enum for renderer alignment
     */
    typedef enum RendererAlign
    {
        Left        = 1 << 0,
        HCenter     = 1 << 1,
        Right       = 1 << 2,
        Top         = 1 << 3,
        VCenter     = 1 << 4,
        Bottom      = 1 << 5,
        BaseLine    = 1 << 6,
    } RendererAlign;

    /**
     * Enum for content alignment
     */
    typedef enum Alignment
    {
        // Content is vertically aligned at the top, and horizontally aligned on the left.
        TopLeft = Left | Top,
        // Content is vertically aligned at the top, and horizontally aligned at the center.
        TopCenter = HCenter | Top,
        // Content is vertically aligned at the top, and horizontally aligned on the right.
        TopRight = Right | Top,
        // Content is vertically aligned in the middle, and horizontally aligned on the left.
        MiddleLeft = Left | VCenter,
        // Content is vertically aligned in the middle, and horizontally aligned at the center.
        MiddleCenter = HCenter | VCenter,
        // Content is vertically aligned in the middle, and horizontally aligned on the right.
        MiddleRight = Right | VCenter,
        // Content is vertically aligned at the bottom, and horizontally aligned on the left.
        BottomLeft = Left | Bottom,
        // Content is vertically aligned at the bottom, and horizontally aligned at the center.
        BottomCenter = HCenter | Bottom,
        // Content is vertically aligned at the bottom, and horizontally aligned on the right.
        BottomRight = Right | Bottom,
    } Alignment;

    class Renderer;

    /**
     * The renderer class
     */
    class SGE_API RendererImage
    {
    public:
        /**
         * Destructor
         */
        ~RendererImage();

        /**
         * Get image size
         */
        int2 getImageSize();
        
    protected:
        friend class Renderer;
        RendererImage(Renderer* renderer, int imageId);
        Renderer*   mRenderer;
        int         mImageId;
    };

    /**
     * The renderer paint
     */
    class RendererPaint
    {
    protected:
        friend class Renderer;
        RendererPaint();
        float xform[6];
        float extent[2];
        float radius;
        float feather;
        float4 innerColor;
        float4 outerColor;
        int image;
    };

    /**
     * The 2D renderer for gui render
     */
    class SGE_API Renderer
    {
    public:
        /**
         * Constructor
         */
        Renderer();

        /**
         * Destructor
         */
        virtual ~Renderer();
        
        /**
         * Save current renderer state,
         * And create new state that copy from current
         * @note the save has max count limit
         * @return current state id
         */
        int save();

        /**
         * Restore to target state 
         * @param index The state id by save(), or negative to restore back         
         */
        void restore(int index);

        /**
         * Reset current renderer state to default
         */
        void reset();
        
        /**
         * Sets global alpha for current renderer
         * @param alpha The global alpha in [0, 1]
         */
        void globalAlpha(float alpha);


        /***   [--- Transform ---]   ***/

        /**
         * Reset transform matrix to identity
         */
        void resetTransform();
        
        /**
         * Do a transform
         * @param xform The transform matrix
         */
        void doTransform(const float* xform);

        /**
         * Get current transform matrix
         * @param out_xform The out pointer
         */
        void getCurrentTransform(float* out_xform);

        /**
         * Do a translate transform
         * @param x The x transform
         * @param y The y transform         
         */
        void doTranslate(float x, float y);

        /**
         * Do a rotate transform
         * @param angle The angle by degrees
         */
        void doRotate(float angle);

        /**
         * Do a skew transform by X axis
         * @param angle The angle by degrees
         */
        void doSkewX(float angle);

        /**
         * Do a skew transform by Y axis
         * @param angle The angle by degrees
         */
        void doSkewY(float angle);

        /**
         * Do a scale transform
         * @param x The X axis scale
         * @param y The Y axis scale
         */
        void doScale(float x, float y);


        /***   [--- Scissor ---]   ***/

        /**
         * add a scissor box
         * @param x The box left
         * @param y The box top
         * @param w The box width
         * @param h The box height
         */
        void addScissor(float x, float y, float w, float h);
        
        /**
         * add scissor box that intersect current scissors
         * @param x The box left
         * @param y The box top
         * @param w The box width
         * @param h The box height
         */
        void addIntersectScissor(float x, float y, float w, float h);

        /**
         * Clear all scissors
         */
        void resetScissor();


        /***   [--- Image ---]   ***/

        /**
         * Load image from file name
         * @param file The image file support jpg, png, psd, tga, pic and gif provided by stb_image
         * @param imageFlag The image flag seealse enum ImageFlag
         * @return referenced pointer, null if load faild
         */
        RendererImage loadImage(const char* file, int imageFlag);

        /**
         * Load image from file data
         * @param fileData The image file data support jpg, png, psd, tga, pic and gif provided by stb_image
         * @param dataLen The fileData Length
         * @param imageFlag The image flag seealse enum ImageFlag
         * @return referenced pointer, null if load faild
         */
        RendererImage loadImage(byte* fileData, size_t dataLen, int imageFlag);

        /**
         * Load image from rgba raw data
         * @param rgbaData The rgba data support jpg, png, psd, tga, pic and gif provided by stb_image
         * @param w The width of image
         * @param h The height of image
         * @param imageFlag The image flag seealse enum ImageFlag
         * @return referenced pointer, null if load faild
         */
        RendererImage loadImage(const byte* rgbaData, int w, int h, int imageFlags);


        /***   [--- Paint ---]   ***/
        
        /**
         * Create linear gradient paint
         */
        RendererPaint createLinearGradient(float sx, float sy, float ex, float ey,
            const float4& icol, const float4& ocol);

        /**
         * Create box gradient paint
         */
        RendererPaint createBoxGradient(float x, float y, float w, float h, float r, float f,
            const float4& icol, const float4& ocol);

        /**
         * Create radial gradient paint
         */
        RendererPaint createRadialGradient(float cx, float cy, float inr, float outr,
            const float4& icol, const float4& ocol);

        /**
         * Create image pattern paint
         */
        RendererPaint createImagePattern(float ox, float oy, float ex, float ey,
            float angle, int image, float alpha);       


        /***   [--- Path ---]   ***/

        /**
         * Begin create path, clear the current path and sub-paths
         */
        void beginPath();
        
        /**
         * Starts new sub-path with specified point as first point
         */
        void moveTo(float x, float y);

        /**
         * Adds line segment from the last point in the path to the specified point
         */
        void lineTo(float x, float y);

        /**
         * Adds cubic bezier segment from last point in the path via two control points to the specified point
         */
        void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);

        /**
         * Adds quadratic bezier segment from last point in the path via a control point to the specified point
         */
        void quadTo(float c1x, float c1y, float x, float y);

        /**
         * Adds an arc segment at the corner defined by the last path point, and two specified points
         */
        void arcTo(float x1, float y1, float x2, float y2, float radius);
        
        /**
         * Closes current sub-path with a line segment
         */
        void closePath();

        /**
         * Sets the current sub-path winding
         */
        void pathWinding(bool solid);

        /**
         * Creates new circle arc shaped sub - path
         */
        void arc(float centerX, float centerY, float radius, float startAngle, float endAngle, bool ccw);
        
        /**
         * Creates new rectangle shaped sub-path
         */
        void rect(float x, float y, float w, float h);

        /**
         * Creates new rounded rectangle shaped sub-path
         */
        void roundedRect(float x, float y, float w, float h, float radius) { roundedRect(x, y, w, h, radius, radius, radius, radius); }
        
        /**
         * Creates new rounded rectangle shaped sub-path
         */
        void roundedRect(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft);
        
        /**
         * Creates new ellipse shaped sub-path
         */
        void ellipse(float cx, float cy, float rx, float ry);

        /**
         * Creates new circle shaped sub-path
         */
        void circle(float cx, float cy, float radius);

        /**
         * Fills the current path with current fill style
         */
        void fillPath();
        
        /**
         * Fills the current path with current stroke style
         */
        void strokePath();

        /**
         * Sets how the end of the line (cap) is drawn
         */
        void setLineCap(LineCapType type);

        /**
         * Sets how sharp path corners are drawn
         */
        void setLineJoin(LineJoinType type);

        /**
         * Sets whether to draw antialias for nvgStroke() and nvgFill(). It's enabled by default
         */
        void setShapeAntiAlias(bool enable);

        /**
         * Sets current stroke style to a solid color
         */
        void setStrokeColor(float r, float g, float b, float a);

        /**
         * Sets current stroke style to a paint, which can be a one of the gradients or a pattern
         */
        void setStrokePaint(const RendererPaint& paint);

        /**
         * Sets current fill style to a solid color
         */
        void setFillColor(float r, float g, float b, float a);

        /**
         * Sets current fill style to a solid color
         */
        void setFillColor(const float4& color);

        /**
         * Sets current fill style to a paint, which can be a one of the gradients or a pattern
         */
        void setFillPaint(const RendererPaint& paint);

        /**
         * Sets the miter limit of the stroke style
         * Miter limit controls when a sharp corner is beveled
         */
        void setMiterLimit(float limit);

        /**
         * Sets the stroke width for strokePath()
         */
        void setStrokeWidth(float size);


        /***   [--- Text ---]   ***/

        /**
         * Creates font by loading it from the disk from specified file name
         * Returns handle to the font, or -1 if failed
         */
        int loadFont(const char* name, const char* filename);

        /**
         * Creates font by loading it from the specified memory chunk
         * Returns handle to the font, or -1 if failed
         */
        int loadFontMem(const char* name, unsigned char* data, int ndata, int freeData);

        /**
         * Finds a loaded font of specified name, and returns handle to it, or -1 if the font is not found
         */
        int findFont(const char* name);

        /**
         * Adds a fallback font by loaded font handle
         */
        int addFallbackFontId(int baseFont, int fallbackFont);

        /**
         * Adds a fallback font by loaded font name
         */
        int addFallbackFont(const char* baseFont, const char* fallbackFont);

        /**
         * Sets the font size of current text style
         */
        void setFontSize(float size);

        /**
         * Sets the blur of current text style
         */
        void setFontBlur(float blur);

        /**
         * Sets the letter spacing of current text style
         */
        void setTextLetterSpacing(float spacing);

        /**
         * Sets the proportional line height of current text style
         * The line height is specified as multiple of font size
         */
        void setTextLineHeight(float lineHeight);

        /**
         * Sets the text align of current text style
         */
        void setTextAlign(Alignment align);

        /**
         * Sets the font face based on specified id of current text style
         */
        void setFont(int font);
        
        /**
         * Sets the font face based on font name of current text style
         */
        void setFont(const char* name);

        /**
         * Draws text string at specified location. If end is specified only the sub-string up to the end is drawn
         */
        float drawText(float x, float y, const char* string, const char* end);

        /**
         * Draws multi-line text string at specified location wrapped at the specified width. If end is specified only the sub-string up to the end is drawn
         * White space is stripped at the beginning of the rows, the text is split at word boundaries or when new-line characters are encountered
         * Words longer than the max width are slit at nearest character (i.e. no hyphenation)
         */
        void drawTextBox(float x, float y, float breakRowWidth, const char* string, const char* end);

        /**
         * Measures the specified text string. Parameter bounds should be a pointer to float[4],
         * if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
         * Returns the horizontal advance of the measured text (i.e. where the next character should drawn).
         * Measured values are returned in local coordinate space.
         */
        float measureText(float x, float y, const char* string, const char* end, float* bounds);
        
        /**
         * Measures the specified multi-text string. Parameter bounds should be a pointer to float[4],
         * if the bounding box of the text should be returned. The bounds value are [xmin,ymin, xmax,ymax]
         * Measured values are returned in local coordinate space.
         */
        void measureTextBox(float x, float y, float breakRowWidth, const char* string, const char* end, float* bounds);
        
        /**
         * Returns the vertical metrics based on the current text style.
         * Measured values are returned in local coordinate space.
         */
        void getTextMetrics(float* ascender, float* descender, float* lineh);
        
    protected:
        friend class Scene;
        friend class RendererImage;
        friend class RendererPaint;
        void*   mNativeCtx;

        /**
         * Begin a new frame
         * @param w The frame width
         * @param h The frame height
         * @param dip The devicePixelRatio
         */
        void beginFrame(float w, float h, float dpi = 1.0f);

        /**
         * End and commit current frame
         */
        void endFrame();

        /**
         * Cancel current frame, discard the frame data
         */
        void cancelFrame();

    private:
        DISABLE_COPY(Renderer)
    };

}


#endif //! SGE_RENDERER_H
