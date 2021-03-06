
/*
The MIT License

Copyright (c) 2019-Present, ROBERT HOWELL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in-
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _DSL_OSD_BINTR_H
#define _DSL_OSD_BINTR_H

#include "Dsl.h"
#include "DslApi.h"
#include "DslElementr.h"
#include "DslBintr.h"

namespace DSL
{
    
    /**
     * @brief convenience macros for shared pointer abstraction
     */
    #define DSL_OSD_PTR std::shared_ptr<OsdBintr>
    #define DSL_OSD_NEW(name, isClockEnabled) \
        std::shared_ptr<OsdBintr>(new OsdBintr(name, isClockEnabled))

    /**
     * @class OsdBintr
     * @brief Implements an On-Screen-Display bin container
     */
    class OsdBintr : public Bintr
    {
    public: 
    
        /**
         * @brief ctor for the OsdBintr class
         * @param[in] name name to give the new OsdBintr
         * @param[in] isClockEnabled true if clock is to be displayed
         */
        OsdBintr(const char* name, boolean isClockEnabled);

        /**
         * @brief dtor for the OsdBintr class
         */
        ~OsdBintr();

        /**
         * @brief Adds this OsdBintr to a Parent Pipline Bintr
         * @param[in] pParentBintr
         */
        bool AddToParent(DSL_NODETR_PTR pParentBintr);
        
        /**
         * @brief Links all child elements of this OsdBintr
         * @return true if all elements were succesfully linked, false otherwise.
         */
        bool LinkAll();
        
        /**
         * @brief Unlinks all child elements of the OsdBintr
         */
        void UnlinkAll();

        /**
         * @brief Set the Stream Id - for when a child of a Source
         * @param streamId unique Id of the Parent Stream
         */
        void SetStreamId(uint streamId)
        {
            LOG_FUNC();
            
            m_streamId = streamId;
        }
        
        /**
         * @brief Links this OsdBintr back to a source Demuxer element
         * @param[in] pDemuxer to link back to
         * @return true on successful Link false other
         */
        bool LinkToSource(DSL_NODETR_PTR pDemuxer);

        /**
         * @brief Unlinks this OsdBintr from a source Demuxer element
         * @return true on successful Unlink false other
         */
        bool UnlinkFromSource();

        /**
         * @brief Gets the current state of the On-screen clock
         * @param[out] enabled true if the OSD clock is current enabled, false otherwise
         */
        void GetClockEnabled(boolean* enabled);

        /**
         * @brief Sets the current state of the On-screen clock
         * @param[in] enabled true if the OSD clock is to be enabled, false otherwise
         */
        bool SetClockEnabled(boolean enabled);
        
        /**
         * @brief Gets the current X and Y offsets for the OSD clock
         * @param[out] offsetX current offset in the x direction in pixels
         * @param[out] offsetY current offset in the Y direction in pixels
         */
        void GetClockOffsets(uint* offsetX, uint* offsetY);
        
        /**
         * @brief Sets the current X and Y offsets for the OSD clock
         * @param[in] offsetX new offset in the Y direction in pixels
         * @param[in] offsetY new offset in the Y direction in pixels
         * @return true on successful update, false otherwise
         */
        bool SetClockOffsets(uint offsetX, uint offsetY);
        
        /**
         * @brief Gets the current font name and size for the OSD clock
         * @param[out] name name of the current font in use
         * @param[out] size soze of the current font in use
         */
        void GetClockFont(const char** name, uint *size);

        /**
         * @brief Sets the font name and size to use by the OSD clock
         * @param[in] name name of the new font to use
         * @param[in] size size of the new font to use
         * @return true on successful update, false otherwise
         */
        bool SetClockFont(const char* name, uint size);

        /**
         * @brief Gets the current RGB colors for the OSD clock
         * @param[out] red red value currently in use
         * @param[out] green green value curretly in use
         * @param[out] blue blue value currently in use
         */
        void GetClockColor(double* red, double* green, double* blue, double* alpha);

        /**
         * @brief Sets the current RGB colors for OSD clock
         * @param[in] red new red value to use
         * @param[in] green new green value to
         * @param[in] blue new blue value to use
         * @param[in] alpha new alpha value to use
         * @return true on successful update, false otherwise
         */
        bool SetClockColor(double red, double green, double blue, double alpha);

        /**
         * @brief Gets the current crop settings
         * @param[out] left pixels to crop from the left
         * @param[out] top pixels to crop from the top
         * @param[out] width width of the cropped stream in pixels
         * @param[out] height height of the cropped stream in pixels
         */
        void GetCropSettings(uint* left, uint* top, uint* width, uint* height);
        
        /**
         * @brief Sets the GPU ID for all Elementrs
         * @return true if successfully set, false otherwise.
         */
        bool SetGpuId(uint gpuId);

        /**
         * @brief Sets the current crop settings
         * @param[in] left pixels to crop from the left
         * @param[in] top pixels to crop from the top
         * @param[in] width width of the cropped stream in pixels
         * @param[in] height height of the cropped stream in pixels
         * @return true if successfully set, false otherwise.
         */
        bool SetCropSettings(uint left, uint top, uint width, uint height);
        
        /**
         * @brief Updates the Video Converter's crop seetings based on this
         * OsdBintrs current seetings.
         */
        void UpdateCropSetting();

        /**
         * @brief Gets the current state of the Redaction enabled flag
         * @return true if Redaction is current enabled, false otherwise
         */
        bool GetRedactionEnabled();

        /**
         * @brief Sets the current state of the Redaction enabled flag
         * @param[in] enabled true if OSD Redaction is to be enabled, false otherwise
         */
        bool SetRedactionEnabled(bool enabled);
        
        /**
         * @brief Adds a Redaction Class to the OsdBintr
         * @param[in] classId of the Redaction Class to add 
         * @param[in] red red level for the redaction background color [0..1]
         * @param[in] blue blue level for the redaction background color [0..1]
         * @param[in] green green level for the redaction background color [0..1]
         * @param[in] alpha alpha level for the redaction background color [0..1]
         * @return[in] true if the Redaction class could be added successfully, false otherwise
         */
        bool AddRedactionClass(int classId, double red, double blue, double green, double alpha);
        
        /**
         * @brief removes a Redaction Class from this OsdBintr
         * @param classId of the Redaction Class to remove
         * @return 
         */
        bool RemoveRedactionClass(int classId);
        

        /**
         * @brief Handler for performing the redaction service
         * @param pBuffer Batch Meta buffer to process
         * @return true allways 
         */
        bool HandleRedaction(GstBuffer* pBuffer);

    private:

        boolean m_isClockEnabled;
        
        bool m_isRedactionEnabled;
        
        std::map <int, std::shared_ptr<NvOSD_ColorParams>> m_redactionClasses;
        
        std::string m_clockFont;
        uint m_clockFontSize;
        uint m_clockOffsetX;
        uint m_clockOffsetY;
        
        NvOSD_ColorParams m_clockColor;

        uint m_cropLeft;
        uint m_cropTop;
        uint m_cropWidth;
        uint m_cropHeight;
        
        /**
         @brief
         */
        guint m_processMode;

        /**
         * @brief Unique streamId of Parent SourceBintr if added to Source vs. Pipeline
         * The id is used when getting a request Pad for Src Demuxer
         */
        int m_streamId;
        
        DSL_ELEMENT_PTR m_pQueue;
        DSL_ELEMENT_PTR m_pVidPreConv;
        DSL_ELEMENT_PTR m_pConvQueue;
        DSL_ELEMENT_PTR m_pOsd;
    
    };
    
    /**
     * @brief Callback function of type dsl_batch_meta_handler_cb ot invoke OsdBintr::HandleRedaction
     * @param batch_meta buffer to process and redact
     * @param user_data instance of OsdBintr (this*) to invoke
     * @return the result return from OsdBintr::HandleRedaction
     */
    static boolean RedactionBatchMetaHandler(void* batch_meta, void* user_data);
}

#endif // _DSL_OSD_BINTR_H