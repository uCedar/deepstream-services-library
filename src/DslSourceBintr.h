
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

#ifndef _DSL_SOURCE_BINTR_H
#define _DSL_SOURCE_BINTR_H

#include "Dsl.h"
#include "DslBintr.h"

namespace DSL
{
    /**
     * @class SourceBintr
     * @brief Implements a Source Bintr for all derived Source types.
     * CSI, V4L2, URI, and RTSP
     */
    class SourceBintr : public Bintr
    {
    public: 
    
        SourceBintr(const char* source);

        SourceBintr(const char* source, guint width, guint height, 
            guint fps_n, guint fps_d);

        ~SourceBintr();

        void AddToParent(std::shared_ptr<Bintr> pParentBintr);

        bool IsMyParent(std::shared_ptr<Bintr> pParentBintr);
                        
        void RemoveFromParent(std::shared_ptr<Bintr> pParentBintr);
        
        /**
         * @brief returns the current, sensor Id as managed by the Parent pipeline
         * @return -1 when source Id is not assigned, i.e. source is not currently in use
         * Unique source Id [0...MAX] when the source is in use.
         */
        int GetSensorId();
        
        /**
         * @brief Sets the unique sensor id for this Source bintr
         * @param id value to assign [0...MAX]
         * @return true if the value was set correctly. 
         */
        bool SetSensorId(int id);
        
        std::shared_ptr<StaticPadtr> m_pStaticSourcePadtr;        

    protected:
            
        /**
         * @brief unique stream source identifier managed by the 
         * parent pipeline from Source add until removed
         */
        int m_sensorId;
        
        /**
         * @brief
         */
        gboolean m_isLive;

        /**
         * @brief
         */
        guint m_width;

        /**
         * @brief
         */
        guint m_height;

        /**
         * @brief
         */
        guint m_fps_n;

        /**
         * @brief
         */
        guint m_fps_d;

        /**
         * @brief
         */
        guint m_latency;

        /**
         * @brief
         */
        guint m_numDecodeSurfaces;

        /**
         * @brief
         */
        guint m_numExtraSurfaces;

        /**
         * @brief
         */
        GstElement * m_pSourceElement;
        
    };

    /**
     * @class CsiSourceBintr
     * @brief 
     */
    class CsiSourceBintr : public SourceBintr
    {
    public: 
    
        CsiSourceBintr(const char* source, guint width, guint height, 
            guint fps_n, guint fps_d);

        ~CsiSourceBintr();
        
    private:
        /**
         * @brief
         */
        GstElement * m_pCapsFilter;
    };


    /**
     * @class UriSourceBintr
     * @brief 
     */
    class UriSourceBintr : public SourceBintr
    {
    public: 
    
        UriSourceBintr(const char* source, const char* uri, 
            guint cudadecMemType, guint intraDecode);

        ~UriSourceBintr();
        
        /**
         * @brief 
         * @param pBin
         * @param pPad
         */
        void HandleOnPadAdded(GstElement* pBin, GstPad* pPad);
        
        /**
         * @brief 
         * @param pChildProxy
         * @param pObject
         * @param name
         */
        void HandleOnChildAdded(GstChildProxy* pChildProxy, 
            GObject* pObject, gchar* name);
        
        /**
         * @brief 
         * @param pObject
         * @param arg0
         */
        void HandleOnSourceSetup(GstElement* pObject, GstElement* arg0);

        /**
         * @brief 
         * @param pPad
         * @param pInfo
         * @return 
         */
        GstPadProbeReturn HandleStreamBufferRestart(GstPad* pPad, GstPadProbeInfo* pInfo);
        
        /**
         * @brief 
         * @return 
         */
        gboolean HandleStreamBufferSeek();
        
    private:

        /**
         * @brief
         */
        std::string m_uriString; 
        
        /**
         * @brief
         */
        guint m_cudadecMemtype;
        
        /**
         * @brief
         */
        guint m_intraDecode;
        
        /**
         * @brief
         */
        guint m_dropFrameInterval;
        
        /**
         * @brief
         */
        guint m_accumulatedBase;

        /**
         * @brief
         */
        guint m_prevAccumulatedBase;
        
        /**
         * @brief
         */
        guint m_bufferProbeId;

        /**
         * @brief
         */
        GstElement* m_pTee;

        /**
         @brief
         */
        GstElement* m_pSourceQueue;

        /**
         * @brief
         */
        GstElement* m_pFakeSink;

        /**
         * @brief
         */
        GstElement* m_pFakeSinkQueue;
    };
}

#endif // _DSL_SOURCE_BINTR_H
