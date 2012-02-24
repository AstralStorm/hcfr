#include "ArgyllMeterWrapper.h"
#include <stdexcept>
#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>
#include <map>

// this is not really a unit test
// but really a description of how to use the interface
// of the class and a test harness if no meter is attached it passes

#define THIS_TEST_CASE ArgyllMeterWrapperTestCase

class THIS_TEST_CASE : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(THIS_TEST_CASE);
    CPPUNIT_TEST( autoDetectMeter );
    CPPUNIT_TEST( NumSupportedUSBMeters );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {
    }

protected:

    // show how calibration works
    // we need to keep showing the user instructions
    // and then allowing the user to control when the calibration function
    // is called. On exit the meter should be calibrated
    void doCalibration(ArgyllMeterWrapper& meter)
    {
        ArgyllMeterWrapper::eMeterState state(ArgyllMeterWrapper::NEEDS_MANUAL_CALIBRATION);
        while(state != ArgyllMeterWrapper::READY)
        {
            std::string meterInstructions(meter.getCalibrationInstructions());
            if(meterInstructions.empty())
            {
                break;
            }
            std::cout << meterInstructions << std::endl;
            // would normally pause here
            state = meter.calibrate();
            if(state == ArgyllMeterWrapper::INCORRECT_POSITION)
            {
                std::cout << meter.getIncorrectPositionInstructions() << std::endl;
                // would normally pause here
            }
        }
    }

    // demonstrate how to open a meter, calibrate it
    // and then take a reading coping with all possible
    // normal returns from the functions
    // the sections showing where to pause would be where
    // the UI is expected to show the relevant text and allow the
    // user to indicate when they are ready to move to the next step
    void autoDetectMeter()
    {
        ArgyllMeterWrapper meter(ArgyllMeterWrapper::AUTODETECT, ArgyllMeterWrapper::CRT, ArgyllMeterWrapper::PROJECTOR, 1);

        std::string errorDescription;
        if(!meter.connectAndStartMeter(errorDescription))
        {
            std::cout << errorDescription << std::endl;
            return;
        }

        std::cout << ArgyllMeterWrapper::getMeterName(meter.getType()) << " meter found" << std::endl;

        if(meter.doesMeterSupportCalibration())
        {
            doCalibration(meter);
        }
        ArgyllMeterWrapper::eMeterState state(ArgyllMeterWrapper::NEEDS_MANUAL_CALIBRATION);
        while(state != ArgyllMeterWrapper::READY)
        {
            state = meter.takeReading();
            if(state == ArgyllMeterWrapper::NEEDS_MANUAL_CALIBRATION)
            {
                doCalibration(meter);
            }
            if(state == ArgyllMeterWrapper::INCORRECT_POSITION)
            {
                std::cout << meter.getIncorrectPositionInstructions() << std::endl;
                // would normally pause here
            }
        }
        CColor reading(meter.getLastReading());
        std::cout << reading << std::endl;
    }
    void NumSupportedUSBMeters()
    {
        std::map<string, ArgyllMeterWrapper::eMeterType> usbMeters;
        for(int i = ArgyllMeterWrapper::AUTODETECT; 
            i < ArgyllMeterWrapper::LAST_METER;
            ++i)
        {
            ArgyllMeterWrapper::eMeterType type = static_cast<ArgyllMeterWrapper::eMeterType>(i);
            if(ArgyllMeterWrapper::isMeterUSB(type))
            {
                usbMeters[ArgyllMeterWrapper::getMeterName(type)] = type;
            }
        }
        CPPUNIT_ASSERT_EQUAL( usbMeters.size(), size_t(12));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(THIS_TEST_CASE);