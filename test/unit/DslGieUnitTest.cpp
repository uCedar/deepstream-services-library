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

#include "catch.hpp"
#include "DslGieBintr.h"

using namespace DSL;

SCENARIO( "A new PrimaryGieBintr is created correctly",  "[PrimaryGieBintr]" )
{
    GIVEN( "Attributes for a new PrimaryGieBintr" ) 
    {
        std::string primaryGieName = "primary-gie";
        std::string inferConfigFile = "./test/configs/config_infer_primary_nano.txt";
        std::string modelEngineFile = "./test/models/Primary_Detector_Nano/resnet10.caffemodel";
        
        uint interval(1);
        uint uniqueId(0);

        WHEN( "A new PrimaryGieBintr is created" )
        {
            
            DSL_PRIMARY_GIE_PTR pPrimaryGieBintr = 
                DSL_PRIMARY_GIE_NEW(primaryGieName.c_str(), inferConfigFile.c_str(), 
                modelEngineFile.c_str(), interval, uniqueId);

            THEN( "The PrimaryGieBintr's memebers are setup and returned correctly" )
            {
                std::string returnedInferConfigFile = pPrimaryGieBintr->GetInferConfigFile();
                REQUIRE( returnedInferConfigFile == inferConfigFile );

                std::string returnedModelEngineFile = pPrimaryGieBintr->GetModelEngineFile();
                REQUIRE( returnedModelEngineFile == modelEngineFile );
                
                REQUIRE( interval == pPrimaryGieBintr->GetInterval() );
                REQUIRE( uniqueId == pPrimaryGieBintr->GetUniqueId() );
                
                REQUIRE( pPrimaryGieBintr->IsLinked() == false );
            }
        }
    }
}

SCENARIO( "A new PrimaryGieBintr can LinkAll Child Elementrs",  "[PrimaryGieBintr]" )
{
    GIVEN( "A new PrimaryGieBintr in an Unlinked state" ) 
    {
        std::string primaryGieName = "primary-gie";
        std::string inferConfigFile = "./test/configs/config_infer_primary_nano.txt";
        std::string modelEngineFile = "./test/models/Primary_Detector_Nano/resnet10.caffemodel";
        
        uint interval(1);
        uint uniqueId(0);

        DSL_PRIMARY_GIE_PTR pPrimaryGieBintr = 
            DSL_PRIMARY_GIE_NEW(primaryGieName.c_str(), inferConfigFile.c_str(), 
            modelEngineFile.c_str(), interval, uniqueId);

        WHEN( "A new PrimaryGieBintr is Linked" )
        {
            REQUIRE( pPrimaryGieBintr->LinkAll() == true );
            
            THEN( "The PrimaryGieBintr IsLinked state is updated correctly" )
            {
                
                REQUIRE( pPrimaryGieBintr->IsLinked() == true );
            }
        }
    }
}

SCENARIO( "A Linked PrimaryGieBintr can UnlinkAll Child Elementrs",  "[PrimaryGieBintr]" )
{
    GIVEN( "A Linked PrimaryGieBintr" ) 
    {
        std::string primaryGieName = "primary-gie";
        std::string inferConfigFile = "./test/configs/config_infer_primary_nano.txt";
        std::string modelEngineFile = "./test/models/Primary_Detector_Nano/resnet10.caffemodel";
        
        uint interval(1);
        uint uniqueId(0);

        DSL_PRIMARY_GIE_PTR pPrimaryGieBintr = 
            DSL_PRIMARY_GIE_NEW(primaryGieName.c_str(), inferConfigFile.c_str(), 
            modelEngineFile.c_str(), interval, uniqueId);

        REQUIRE( pPrimaryGieBintr->LinkAll() == true );

        WHEN( "A new PrimaryGieBintr is created" )
        {
            pPrimaryGieBintr->UnlinkAll();
            
            THEN( "The PrimaryGieBintr can LinkAll Child Elementrs" )
            {
                
                REQUIRE( pPrimaryGieBintr->IsLinked() == false );
            }
        }
    }
}