#pragma once

#include <sepia.hpp>
#include <opalkellyfrontpanel.h>

#include <algorithm>

/// opalKellyAtisSepia specialises Sepia for the Opal Kelly ATIS.
/// In order to use this header, an application must link to the dynamic library opalkellyfrontpanel.
namespace opalKellyAtisSepia {

    /// Camera represents an ATIS connected to an Opal Kelly board.
    class Camera {
        public:

            /// availableSerials returns the connected Opal Kelly ATIS cameras' serials.
            static std::unordered_set<std::string> availableSerials() {
                auto opalKellyFrontPanel = OpalKellyLegacy::okCFrontPanel();
                auto serials = std::unordered_set<std::string>();
                for (auto deviceIndex = 0; deviceIndex < opalKellyFrontPanel.GetDeviceCount(); ++deviceIndex) {
                    serials.insert(opalKellyFrontPanel.GetDeviceListSerial(deviceIndex));
                }
                return serials;
            }

            /// defaultParameter returns the default parameter used by the Opal Kelly ATIS.
            static std::unique_ptr<sepia::Parameter> defaultParameter() {
                return sepia::make_unique<sepia::ObjectParameter>(
                    "firmware",                    sepia::make_unique<sepia::StringParameter>("/usr/local/share/opalKellyAtisSepia/atis.1.2.0.bit"),
                    "exposureMeasurementTrigger",  sepia::make_unique<sepia::EnumParameter>("changeDetection", std::unordered_set<std::string>({
                        "changeDetection",
                        "sequential",
                        "manual",
                    })),
                    "columnsSelection",            sepia::ListParameter::makeEmpty(sepia::make_unique<sepia::NumberParameter>(304, 1, 305, true)),
                    "selectFirstColumn",           sepia::make_unique<sepia::BooleanParameter>(true),
                    "rowsSelection",               sepia::ListParameter::makeEmpty(sepia::make_unique<sepia::NumberParameter>(240, 1, 241, true)),
                    "selectFirstRow",              sepia::make_unique<sepia::BooleanParameter>(true),
                    "selectionIsRegionOfInterest", sepia::make_unique<sepia::BooleanParameter>(false),
                    "sendFakeEventPeriodically",   sepia::make_unique<sepia::BooleanParameter>(false),
                    "applySelectionTo",            sepia::make_unique<sepia::EnumParameter>("changeDetection", std::unordered_set<std::string>({
                        "changeDetection",
                        "exposureMeasurement",
                        "changeDetectionAndExposureMeasurement",
                    })),
                    "changeDetection",             sepia::make_unique<sepia::ObjectParameter>(
                        "resetSwitchBulkPotential",     sepia::make_unique<sepia::CharParameter>(207),
                        "photoreceptorFeedback",        sepia::make_unique<sepia::CharParameter>(216),
                        "refractoryPeriod",             sepia::make_unique<sepia::CharParameter>(220),
                        "follower",                     sepia::make_unique<sepia::CharParameter>(235),
                        "eventSourceAmplifier",         sepia::make_unique<sepia::CharParameter>( 38),
                        "onEventThreshold",             sepia::make_unique<sepia::CharParameter>( 34),
                        "offEventThreshold",            sepia::make_unique<sepia::CharParameter>( 48),
                        "offEventInverter",             sepia::make_unique<sepia::CharParameter>( 61),
                        "cascodePhotoreceptorFeedback", sepia::make_unique<sepia::CharParameter>(154)
                    ),
                    "exposureMeasurement",         sepia::make_unique<sepia::ObjectParameter>(
                        "comparatorTail",        sepia::make_unique<sepia::CharParameter>( 40),
                        "comparatorHysteresis",  sepia::make_unique<sepia::CharParameter>( 35),
                        "comparatorOutputStage", sepia::make_unique<sepia::CharParameter>( 51),
                        "upperThreshold",        sepia::make_unique<sepia::CharParameter>(247),
                        "lowerThreshold",        sepia::make_unique<sepia::CharParameter>(231)
                    ),
                    "pullup",                      sepia::make_unique<sepia::ObjectParameter>(
                        "exposureMeasurementAbscissaRequest", sepia::make_unique<sepia::CharParameter>(127),
                        "exposureMeasurementOrdinateRequest", sepia::make_unique<sepia::CharParameter>(155),
                        "changeDetectionAbscissaRequest",     sepia::make_unique<sepia::CharParameter>(151),
                        "changeDetectionOrdinateRequest",     sepia::make_unique<sepia::CharParameter>(120),
                        "abscissaAcknoledge",                 sepia::make_unique<sepia::CharParameter>(162),
                        "abscissaEncoder",                    sepia::make_unique<sepia::CharParameter>(162),
                        "ordinateEncoder",                    sepia::make_unique<sepia::CharParameter>(120)
                    ),
                    "control",                     sepia::make_unique<sepia::ObjectParameter>(
                        "exposureMeasurementTimeout",           sepia::make_unique<sepia::CharParameter>( 42),
                        "sequentialExposureMeasurementTimeout", sepia::make_unique<sepia::CharParameter>( 45),
                        "abscissaAcknoledgeTimeout",            sepia::make_unique<sepia::CharParameter>( 56),
                        "latchCellScanPulldown",                sepia::make_unique<sepia::CharParameter>(134),
                        "abscissaRequestPulldown",              sepia::make_unique<sepia::CharParameter>( 87)
                    )
                );
            }

            /// width returns the sensor width.
            static constexpr std::size_t width() {
                return 304;
            }

            /// height returns the sensor height.
            static constexpr std::size_t height() {
                return 240;
            }

            /// configuration contains the settings for the digital-to-analog converters on the FPGA.
            static std::unordered_map<
                std::string, std::unordered_map<
                    std::string, std::unordered_map<
                        std::string, uint32_t>>> configuration() {
                return std::unordered_map<
                    std::string, std::unordered_map<
                        std::string, std::unordered_map<
                            std::string, uint32_t>>>({
                    {"changeDetection", {
                        {"resetSwitchBulkPotential",     {{"address", 0x02}, {"tension", 0x5900}}},
                        {"photoreceptorFeedback",        {{"address", 0x03}, {"tension", 0x5900}}},
                        {"refractoryPeriod",             {{"address", 0x04}, {"tension", 0x5900}}},
                        {"follower",                     {{"address", 0x05}, {"tension", 0x5900}}},
                        {"eventSourceAmplifier",         {{"address", 0x06}, {"tension", 0x7900}}},
                        {"onEventThreshold",             {{"address", 0x07}, {"tension", 0x7900}}},
                        {"offEventThreshold",            {{"address", 0x08}, {"tension", 0x7900}}},
                        {"offEventInverter",             {{"address", 0x09}, {"tension", 0x7900}}},
                        {"cascodePhotoreceptorFeedback", {{"address", 0x0a}, {"tension", 0x7900}}},
                    }},
                    {"exposureMeasurement", {
                        {"comparatorTail",        {{"address", 0x0b}, {"tension", 0x7900}}},
                        {"comparatorHysteresis",  {{"address", 0x0c}, {"tension", 0x7900}}},
                        {"comparatorOutputStage", {{"address", 0x0d}, {"tension", 0x7900}}},
                        {"upperThreshold",        {{"address", 0x0e}, {"tension", 0x5900}}},
                        {"lowerThreshold",        {{"address", 0x0f}, {"tension", 0x5900}}},
                    }},
                    {"pullup", {
                        {"exposureMeasurementAbscissaRequest", {{"address", 0x10}, {"tension", 0x5900}}},
                        {"exposureMeasurementOrdinateRequest", {{"address", 0x11}, {"tension", 0x5900}}},
                        {"changeDetectionAbscissaRequest",     {{"address", 0x12}, {"tension", 0x5900}}},
                        {"changeDetectionOrdinateRequest",     {{"address", 0x13}, {"tension", 0x5900}}},
                        {"abscissaAcknoledge",                 {{"address", 0x14}, {"tension", 0x5900}}},
                        {"abscissaEncoder",                    {{"address", 0x15}, {"tension", 0x7900}}},
                        {"ordinateEncoder",                    {{"address", 0x16}, {"tension", 0x7900}}},
                    }},
                    {"control", {
                        {"exposureMeasurementTimeout",           {{"address", 0x17}, {"tension", 0x7900}}},
                        {"sequentialExposureMeasurementTimeout", {{"address", 0x18}, {"tension", 0x7900}}},
                        {"abscissaAcknoledgeTimeout",            {{"address", 0x19}, {"tension", 0x7900}}},
                        {"latchCellScanPulldown",                {{"address", 0x1a}, {"tension", 0x7900}}},
                        {"abscissaRequestPulldown",              {{"address", 0x1b}, {"tension", 0x7900}}},
                    }},
                    {"static", {
                        {"resetTimestamp",   {{"address", 0x00}, {"tension", 0x5900}, {"value", 0}}},
                        {"testEvent",        {{"address", 0x01}, {"tension", 0x7900}, {"value", 0}}},
                        {"resetPhotodiodes", {{"address", 0x1c}, {"tension",   0x00}, {"value", 3}}},
                    }},
                });
            }

            Camera() {}
            Camera(const Camera&) = delete;
            Camera(Camera&&) = default;
            Camera& operator=(const Camera&) = delete;
            Camera& operator=(Camera&&) = default;
            virtual ~Camera() {}

            /// trigger sends a trigger signal to the camera.
            /// With default settings, this signal will trigger a change detection on every pixel.
            virtual void trigger() = 0;
    };

    /// SpecialisedCamera represents a template-specialised ATIS connected to an Opal Kelly board.
    template <typename HandleEvent, typename HandleException>
    class SpecialisedCamera : public Camera, public sepia::SpecialisedCamera<sepia::AtisEvent, HandleEvent, HandleException> {
        public:
            SpecialisedCamera<HandleEvent, HandleException>(
                HandleEvent handleEvent,
                HandleException handleException,
                std::unique_ptr<sepia::UnvalidatedParameter> unvalidatedParameter,
                std::size_t fifoSize,
                std::string serial,
                std::chrono::milliseconds sleepDuration
            ) :
                sepia::SpecialisedCamera<sepia::AtisEvent, HandleEvent, HandleException>(
                    std::forward<HandleEvent>(handleEvent),
                    std::forward<HandleException>(handleException),
                    fifoSize,
                    sleepDuration
                ),
                _parameter(defaultParameter()),
                _acquisitionRunning(true),
                _timestampOffset(0)
            {
                if (unvalidatedParameter->isString()) {
                    _parameter->load(unvalidatedParameter->jsonData());
                } else {
                    _parameter->load(unvalidatedParameter->parameter());
                }

                // check wether the serial exists and is an ATIS camera
                // cefault to the first serial found if an empty string is given as serial
                {
                    const auto serials = availableSerials();
                    if (serials.empty()) {
                        throw sepia::NoDeviceConnected("Opal Kelly ATIS");
                    } else {
                        if (serial.empty()) {
                            serial = *serials.begin();
                        } else if (serials.find(serial) == serials.end()) {
                            throw std::range_error("The device with the given serial is not plugged in");
                        }
                    }
                }

                // open the connection to the ATIS
                {
                    const auto serialError = _opalKellyFrontPanel.OpenBySerial(serial);
                    if (serialError != okCFrontPanel::NoError) {
                        throw std::runtime_error("Connection to the serial '" + serial + "' raised the error " + std::to_string(serialError));
                    }
                }

                // load the defaut PLL configuration
                {
                    const auto pllError = _opalKellyFrontPanel.LoadDefaultPLLConfiguration();
                    if (pllError != okCFrontPanel::NoError) {
                        throw std::runtime_error("The default PLL configuration loading raised the error " + std::to_string(pllError));
                    }
                }

                // load the firmware
                {
                    std::string firmwareFilename = _parameter->getString({"firmware"});
                    std::ifstream firmwareFile(firmwareFilename);
                    if (!firmwareFile.good()) {
                        throw std::runtime_error("The firmware file '" + firmwareFilename + "' does not exist or is not readable");
                    }

                    const auto firmwareError = _opalKellyFrontPanel.ConfigureFPGA(firmwareFilename);
                    if (firmwareError != okCFrontPanel::NoError) {
                        throw std::runtime_error("The firmware loading from file '" + firmwareFilename + "' raised the error " + std::to_string(firmwareError));
                    }
                }

                // open the biases and selection settings
                _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 5, 1 << 5);
                _opalKellyFrontPanel.UpdateWireIns();

                // initialise the digital-to-analog converters (biases setup)
                for (const auto& categoryPair : configuration()) {
                    for (const auto& settingPair : categoryPair.second) {
                        _opalKellyFrontPanel.SetWireInValue(0x01,
                            categoryPair.first == "static" ?
                                settingPair.second.at("value")
                                : static_cast<uint32_t>(_parameter->getNumber({categoryPair.first, settingPair.first}))
                        );
                        _opalKellyFrontPanel.SetWireInValue(0x02, settingPair.second.at("tension"));
                        _opalKellyFrontPanel.SetWireInValue(0x03, settingPair.second.at("address"));
                        _opalKellyFrontPanel.UpdateWireIns();
                        _opalKellyFrontPanel.ActivateTriggerIn(0x40, 1);
                    }
                }
                _opalKellyFrontPanel.ActivateTriggerIn(0x40, 6);

                // load the region of interest parameters
                if (_parameter->getListParameter({"columnsSelection"}).size() > 0 || _parameter->getListParameter({"rowsSelection"}).size() > 0) {

                    // compute the columns fill bits
                    auto fill = std::vector<bool>();
                    fill.reserve(544);
                    if (_parameter->getListParameter({"columnsSelection"}).size() > 0) {
                        auto state = _parameter->getBoolean({"selectFirstColumn"});
                        auto firstPass = true;
                        while (fill.size() < 304) {
                            for (const auto& columnCount : _parameter->getListParameter({"columnsSelection"})) {
                                for (uint16_t index = 0; index < static_cast<uint16_t>(columnCount->getNumber({})); ++index) {
                                    if (fill.size() >= 304) {
                                        if (firstPass) {
                                            throw std::runtime_error("The columns selection sum is larger than 304");
                                        } else {
                                            break;
                                        }
                                    }
                                    fill.push_back(state);
                                }
                                state = !state;
                            }
                            if (firstPass) {
                                firstPass = false;
                            }
                        }
                        std::reverse(fill.begin(), fill.end());
                    } else {
                        fill = std::vector<bool>(304);
                    }

                    // compute the rows fill bits
                    if (_parameter->getListParameter({"rowsSelection"}).size() > 0) {
                        auto state = _parameter->getBoolean({"selectFirstRow"});
                        auto firstPass = true;
                        while (fill.size() < 544) {
                            for (const auto& columnCount : _parameter->getListParameter({"rowsSelection"})) {
                                for (uint16_t index = 0; index < static_cast<uint16_t>(columnCount->getNumber({})); ++index) {
                                    if (fill.size() >= 544) {
                                        if (firstPass) {
                                            throw std::runtime_error("The rows selection sum is larger than 240");
                                        } else {
                                            break;
                                        }
                                    }
                                    fill.push_back(state);
                                }
                                if (fill.size() >= 544) {
                                    break;
                                }
                                state = !state;
                            }
                            if (firstPass) {
                                firstPass = false;
                            }
                        }
                        std::reverse(fill.begin() + 304, fill.end());
                    } else {
                        auto fillRows = std::vector<bool>(240);
                        fill.insert(fill.end(), fillRows.begin(), fillRows.end());
                    }

                    // pack the fill bits as 16 bits values for sending to the Opal Kelly
                    uint16_t pack = 0;
                    std::size_t packIndex = 0;

                    for (auto fillIterator = fill.begin(); fillIterator != fill.end(); ++fillIterator) {
                        if (*fillIterator) {
                            pack &= ~(1 << packIndex);
                        } else {
                            pack |= 1 << packIndex;
                        }

                        if (packIndex == 15) {
                            _opalKellyFrontPanel.SetWireInValue(0x01, pack);
                            _opalKellyFrontPanel.SetWireInValue(0x02, static_cast<uint32_t>((fillIterator - fill.begin()) / 16));
                            _opalKellyFrontPanel.UpdateWireIns();
                            _opalKellyFrontPanel.ActivateTriggerIn(0x40, 3);
                            packIndex = 0;
                        } else {
                            ++packIndex;
                        }
                    }
                    _opalKellyFrontPanel.ActivateTriggerIn(0x40, 4);

                    // define wether the pixels outside the selection are disabled, or wether the ones inside are
                    _opalKellyFrontPanel.SetWireInValue(0x00, _parameter->getBoolean({"selectionIsRegionOfInterest"}) ? 1 << 9 : 0, 1 << 9);
                    _opalKellyFrontPanel.UpdateWireIns();

                    // define which part of the pixels the selection is applied to
                    if (
                        _parameter->getString({"applySelectionTo"}) == "changeDetection"
                        || _parameter->getString({"applySelectionTo"}) == "changeDetectionAndExposureMeasurement"
                    ) {
                        _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 4, 1 << 4);
                        _opalKellyFrontPanel.UpdateWireIns();
                    }
                    if (
                        _parameter->getString({"applySelectionTo"}) == "exposureMeasurement"
                        || _parameter->getString({"applySelectionTo"}) == "changeDetectionAndExposureMeasurement"
                    ) {
                        _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 3, 1 << 3);
                        _opalKellyFrontPanel.UpdateWireIns();
                    }
                }

                // close the biases and selection settings
                _opalKellyFrontPanel.SetWireInValue(0x00, 0, 1 << 5);
                _opalKellyFrontPanel.UpdateWireIns();

                // load the exposure measurement trigger
                if (_parameter->getString({"exposureMeasurementTrigger"}) == "changeDetection") {
                    _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 0, 1 << 0);
                    _opalKellyFrontPanel.UpdateWireIns();
                } else if (_parameter->getString({"exposureMeasurementTrigger"}) == "sequential") {
                    _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 1, 1 << 1);
                    _opalKellyFrontPanel.UpdateWireIns();

                    if (
                        _parameter->getString({"applySelectionTo"}) == "changeDetection"
                        || _parameter->getString({"applySelectionTo"}) == "changeDetectionAndExposureMeasurement"
                    ) {
                        _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 0, 1 << 0);
                        _opalKellyFrontPanel.UpdateWireIns();
                    }
                }

                // reset the Atis FIFO
                _opalKellyFrontPanel.ActivateTriggerIn(0x40, 7);

                // reset the handlers
                _opalKellyFrontPanel.ActivateTriggerIn(0x40, 2);

                // enable periodic fake events
                if (_parameter->getBoolean({"sendFakeEventPeriodically"})) {
                    _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 12, 1 << 12);
                    _opalKellyFrontPanel.UpdateWireIns();
                }

                // start the FPGA events reading
                _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 10, 1 << 10);
                _opalKellyFrontPanel.UpdateWireIns();

                // start the reading loop
                _acquisitionLoop = std::thread([this, serial]() -> void {
                    try {
                        auto event = sepia::AtisEvent{};
                        auto eventsData = std::vector<uint8_t>((1 << 24) * 4);
                        while (_acquisitionRunning.load(std::memory_order_relaxed)) {
                            _opalKellyFrontPanel.UpdateWireOuts();
                            const auto numberOfEvents = (_opalKellyFrontPanel.GetWireOutValue(0x21) << 21) + (_opalKellyFrontPanel.GetWireOutValue(0x20) << 5);
                            if (numberOfEvents > 1 << 24) {
                                const auto serials = availableSerials();
                                if (serials.find(serial) == serials.end()) {
                                    throw sepia::DeviceDisconnected("Opal Kelly ATIS");
                                } else {
                                    throw std::runtime_error("Opal Kelly ATIS's FIFO overflow");
                                }
                            } else if (numberOfEvents > 0) {
                                _opalKellyFrontPanel.ReadFromPipeOut(0xa0, numberOfEvents * 4, eventsData.data());
                                for (unsigned long eventIndex = 0; eventIndex < numberOfEvents; ++eventIndex) {
                                    const auto eventByteIterator = std::next(eventsData.begin(), 4 * eventIndex);
                                    if (*std::next(eventByteIterator, 3) == 0x80) {
                                        _timestampOffset = (
                                            static_cast<uint64_t>(*eventByteIterator)
                                            | (static_cast<uint64_t>(*std::next(eventByteIterator, 1)) << 8)
                                            | (static_cast<uint64_t>(*std::next(eventByteIterator, 2)) << 16)
                                        ) * 0x800;
                                    } else {
                                        event.x = (static_cast<uint16_t>(*std::next(eventByteIterator, 2) & 0x1) << 8) + *std::next(eventByteIterator, 1);
                                        event.y = 239 - *eventByteIterator;
                                        event.timestamp = _timestampOffset + (
                                            (static_cast<uint64_t>((*std::next(eventByteIterator, 3) & 0xf)) << 7)
                                            | (*std::next(eventByteIterator, 2) >> 1)
                                        );
                                        event.polarity = ((*std::next(eventByteIterator, 3) & 0b10000) >> 4) == 1;
                                        event.isThresholdCrossing = ((*std::next(eventByteIterator, 3) & 0b100000) >> 5) == 1;
                                        if (!this->push(event)) {
                                            throw std::runtime_error("Computer's FIFO overflow");
                                        }
                                    }
                                }
                            } else {
                                std::this_thread::sleep_for(this->_sleepDuration);
                            }
                        }
                    } catch (...) {
                        this->_handleException(std::current_exception());
                    }
                });
            }
            SpecialisedCamera(const SpecialisedCamera&) = delete;
            SpecialisedCamera(SpecialisedCamera&&) = default;
            SpecialisedCamera& operator=(const SpecialisedCamera&) = delete;
            SpecialisedCamera& operator=(SpecialisedCamera&&) = default;
            virtual ~SpecialisedCamera() {
                _acquisitionRunning.store(false, std::memory_order_relaxed);
                _acquisitionLoop.join();
                if (_opalKellyFrontPanel.IsOpen()) {
                    _opalKellyFrontPanel.Close();
                }
            }
            virtual void trigger() override {
                _opalKellyFrontPanel.SetWireInValue(0x00, 1 << 6, 1 << 6);
                _opalKellyFrontPanel.UpdateWireIns();
                _opalKellyFrontPanel.SetWireInValue(0x00, 0 << 6, 1 << 6);
                _opalKellyFrontPanel.UpdateWireIns();
            }

        protected:
            std::unique_ptr<sepia::Parameter> _parameter;
            std::atomic_bool _acquisitionRunning;
            OpalKellyLegacy::okCFrontPanel _opalKellyFrontPanel;
            std::thread _acquisitionLoop;
            uint64_t _timestampOffset;
    };

    /// make_camera creates a camera from functors.
    template<typename HandleEvent, typename HandleException>
    std::unique_ptr<SpecialisedCamera<HandleEvent, HandleException>> make_camera(
        HandleEvent handleEvent,
        HandleException handleException,
        std::unique_ptr<sepia::UnvalidatedParameter> unvalidatedParameter = sepia::make_unique<sepia::UnvalidatedParameter>(std::string()),
        std::size_t fifoSize = 1 << 24,
        std::string serial = std::string(),
        std::chrono::milliseconds sleepDuration = std::chrono::milliseconds(10)
    ) {
        return sepia::make_unique<SpecialisedCamera<HandleEvent, HandleException>>(
            std::forward<HandleEvent>(handleEvent),
            std::forward<HandleException>(handleException),
            std::move(unvalidatedParameter),
            fifoSize,
            serial,
            sleepDuration
        );
    }
}
