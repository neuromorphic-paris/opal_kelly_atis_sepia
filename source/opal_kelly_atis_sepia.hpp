#pragma once

#include "../resources/opalkellyfrontpanel.h"
#include "../third_party/sepia/source/sepia.hpp"
#include <algorithm>

#include <iostream>

/// opal_kelly_atis_sepia specialises sepia for the Opal Kelly ATIS.
/// In order to use this header, an application must link to the dynamic library opalkellyfrontpanel.
namespace opal_kelly_atis_sepia {

    /// camera represents an ATIS connected to an Opal Kelly board.
    class camera {
        public:
        /// available_serials returns the connected Opal Kelly ATIS cameras' serials.
        static std::unordered_set<std::string> available_serials() {
            OpalKellyLegacy::okCFrontPanel opal_kelly_front_panel;
            std::unordered_set<std::string> serials;
            for (auto device_index = 0; device_index < opal_kelly_front_panel.GetDeviceCount(); ++device_index) {
                serials.insert(opal_kelly_front_panel.GetDeviceListSerial(device_index));
            }
            return serials;
        }

        /// default_parameter returns the default parameter used by the Opal Kelly ATIS.
        static std::unique_ptr<sepia::parameter> default_parameter() {
            return sepia::make_unique<sepia::object_parameter>(
                "firmware",
                sepia::make_unique<sepia::string_parameter>(
                    sepia::join({sepia::dirname(DIRNAME), "resources", "atis.1.1.1.bit"})),
                "exposure_measurement_trigger",
                sepia::make_unique<sepia::enum_parameter>(
                    "change_detection",
                    std::unordered_set<std::string>({
                        "change_detection",
                        "sequential",
                        "manual",
                    })),
                "columns_selection",
                sepia::array_parameter::make_empty(sepia::make_unique<sepia::number_parameter>(304, 1, 305, true)),
                "select_first_column",
                sepia::make_unique<sepia::boolean_parameter>(true),
                "rows_selection",
                sepia::array_parameter::make_empty(sepia::make_unique<sepia::number_parameter>(240, 1, 241, true)),
                "select_first_row",
                sepia::make_unique<sepia::boolean_parameter>(true),
                "selection_is_region_of_interest",
                sepia::make_unique<sepia::boolean_parameter>(false),
                "send_fake_event_periodically",
                sepia::make_unique<sepia::boolean_parameter>(false),
                "apply_selection_to",
                sepia::make_unique<sepia::enum_parameter>(
                    "change_detection",
                    std::unordered_set<std::string>({
                        "change_detection",
                        "exposure_measurement",
                        "change_detection_and_exposure_measurement",
                    })),
                "change_detection",
                sepia::make_unique<sepia::object_parameter>(
                    "reset_switch_bulk_potential",
                    sepia::make_unique<sepia::char_parameter>(207),
                    "photoreceptor_feedback",
                    sepia::make_unique<sepia::char_parameter>(216),
                    "refractory_period",
                    sepia::make_unique<sepia::char_parameter>(220),
                    "follower",
                    sepia::make_unique<sepia::char_parameter>(235),
                    "event_source_amplifier",
                    sepia::make_unique<sepia::char_parameter>(38),
                    "on_event_threshold",
                    sepia::make_unique<sepia::char_parameter>(48),
                    "off_event_threshold",
                    sepia::make_unique<sepia::char_parameter>(34),
                    "off_event_inverter",
                    sepia::make_unique<sepia::char_parameter>(61),
                    "cascode_photoreceptor_feedback",
                    sepia::make_unique<sepia::char_parameter>(154)),
                "exposure_measurement",
                sepia::make_unique<sepia::object_parameter>(
                    "comparator_tail",
                    sepia::make_unique<sepia::char_parameter>(40),
                    "comparator_hysteresis",
                    sepia::make_unique<sepia::char_parameter>(35),
                    "comparator_output_stage",
                    sepia::make_unique<sepia::char_parameter>(51),
                    "upper_threshold",
                    sepia::make_unique<sepia::char_parameter>(247),
                    "lower_threshold",
                    sepia::make_unique<sepia::char_parameter>(231)),
                "pullup",
                sepia::make_unique<sepia::object_parameter>(
                    "exposure_measurement_abscissa_request",
                    sepia::make_unique<sepia::char_parameter>(127),
                    "exposure_measurement_ordinate_request",
                    sepia::make_unique<sepia::char_parameter>(155),
                    "change_detection_abscissa_request",
                    sepia::make_unique<sepia::char_parameter>(151),
                    "change_detection_ordinate_request",
                    sepia::make_unique<sepia::char_parameter>(120),
                    "abscissa_acknoledge",
                    sepia::make_unique<sepia::char_parameter>(162),
                    "abscissa_encoder",
                    sepia::make_unique<sepia::char_parameter>(162),
                    "ordinate_encoder",
                    sepia::make_unique<sepia::char_parameter>(120)),
                "control",
                sepia::make_unique<sepia::object_parameter>(
                    "exposure_measurement_timeout",
                    sepia::make_unique<sepia::char_parameter>(42),
                    "sequential_exposure_measurement_timeout",
                    sepia::make_unique<sepia::char_parameter>(45),
                    "abscissa_acknoledge_timeout",
                    sepia::make_unique<sepia::char_parameter>(56),
                    "latch_cell_scan_pulldown",
                    sepia::make_unique<sepia::char_parameter>(134),
                    "abscissa_request_pulldown",
                    sepia::make_unique<sepia::char_parameter>(87)));
        }

        /// width returns the sensor width.
        static constexpr uint16_t width() {
            return 304;
        }

        /// height returns the sensor height.
        static constexpr uint16_t height() {
            return 240;
        }

        /// configuration contains the settings for the digital-to-analog converters on the FPGA.
        static std::
            unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>>>
            configuration() {
            return {
                {"change_detection",
                 {
                     {"reset_switch_bulk_potential", {{"address", 0x02}, {"tension", 0x5900}}},
                     {"photoreceptor_feedback", {{"address", 0x03}, {"tension", 0x5900}}},
                     {"refractory_period", {{"address", 0x04}, {"tension", 0x5900}}},
                     {"follower", {{"address", 0x05}, {"tension", 0x5900}}},
                     {"event_source_amplifier", {{"address", 0x06}, {"tension", 0x7900}}},
                     {"on_event_threshold", {{"address", 0x07}, {"tension", 0x7900}}},
                     {"off_event_threshold", {{"address", 0x08}, {"tension", 0x7900}}},
                     {"off_event_inverter", {{"address", 0x09}, {"tension", 0x7900}}},
                     {"cascode_photoreceptor_feedback", {{"address", 0x0a}, {"tension", 0x7900}}},
                 }},
                {"exposure_measurement",
                 {
                     {"comparator_tail", {{"address", 0x0b}, {"tension", 0x7900}}},
                     {"comparator_hysteresis", {{"address", 0x0c}, {"tension", 0x7900}}},
                     {"comparator_output_stage", {{"address", 0x0d}, {"tension", 0x7900}}},
                     {"upper_threshold", {{"address", 0x0e}, {"tension", 0x5900}}},
                     {"lower_threshold", {{"address", 0x0f}, {"tension", 0x5900}}},
                 }},
                {"pullup",
                 {
                     {"exposure_measurement_abscissa_request", {{"address", 0x10}, {"tension", 0x5900}}},
                     {"exposure_measurement_ordinate_request", {{"address", 0x11}, {"tension", 0x5900}}},
                     {"change_detection_abscissa_request", {{"address", 0x12}, {"tension", 0x5900}}},
                     {"change_detection_ordinate_request", {{"address", 0x13}, {"tension", 0x5900}}},
                     {"abscissa_acknoledge", {{"address", 0x14}, {"tension", 0x5900}}},
                     {"abscissa_encoder", {{"address", 0x15}, {"tension", 0x7900}}},
                     {"ordinate_encoder", {{"address", 0x16}, {"tension", 0x7900}}},
                 }},
                {"control",
                 {
                     {"exposure_measurement_timeout", {{"address", 0x17}, {"tension", 0x7900}}},
                     {"sequential_exposure_measurement_timeout", {{"address", 0x18}, {"tension", 0x7900}}},
                     {"abscissa_acknoledge_timeout", {{"address", 0x19}, {"tension", 0x7900}}},
                     {"latch_cell_scan_pulldown", {{"address", 0x1a}, {"tension", 0x7900}}},
                     {"abscissa_request_pulldown", {{"address", 0x1b}, {"tension", 0x7900}}},
                 }},
                {"static",
                 {
                     {"reset_t", {{"address", 0x00}, {"tension", 0x5900}, {"value", 0}}},
                     {"test_event", {{"address", 0x01}, {"tension", 0x7900}, {"value", 0}}},
                     {"reset_photodiodes", {{"address", 0x1c}, {"tension", 0x00}, {"value", 3}}},
                 }},
            };
        }

        camera() {}
        camera(const camera&) = delete;
        camera(camera&&) = default;
        camera& operator=(const camera&) = delete;
        camera& operator=(camera&&) = default;
        virtual ~camera() {}

        /// trigger sends a trigger signal to the camera.
        /// with default settings, this signal will trigger a change detection on every pixel.
        virtual void trigger() = 0;
    };

    /// specialized_camera represents a template-specialized ATIS connected to an Opal Kelly board.
    template <typename HandleEvent, typename HandleException>
    class specialized_camera : public camera,
                               public sepia::specialized_camera<sepia::atis_event, HandleEvent, HandleException> {
        public:
        specialized_camera<HandleEvent, HandleException>(
            HandleEvent handle_event,
            HandleException handle_exception,
            std::unique_ptr<sepia::unvalidated_parameter> unvalidated_parameter,
            std::size_t fifo_size,
            std::string serial,
            std::chrono::milliseconds sleep_duration) :
            sepia::specialized_camera<sepia::atis_event, HandleEvent, HandleException>(
                std::forward<HandleEvent>(handle_event),
                std::forward<HandleException>(handle_exception),
                fifo_size,
                sleep_duration),
            _parameter(default_parameter()),
            _acquisition_running(true),
            _t_offset(0) {
            _parameter->parse_or_load(std::move(unvalidated_parameter));

            // check wether the serial exists and is an ATIS camera
            // default to the first serial found if an empty string is given as serial
            {
                const auto serials = available_serials();
                if (serials.empty()) {
                    throw sepia::no_device_connected("Opal Kelly ATIS");
                } else {
                    if (serial.empty()) {
                        serial = *serials.begin();
                    } else if (serials.find(serial) == serials.end()) {
                        throw sepia::no_device_connected("Opal Kelly ATIS");
                    }
                }
            }

            // open the connection to the ATIS
            {
                const auto serial_error = _opal_kelly_front_panel.OpenBySerial(serial);
                if (serial_error != okCFrontPanel::NoError) {
                    throw std::runtime_error(
                        "connection to the serial '" + serial + "' raised the error " + std::to_string(serial_error));
                }
            }

            // load the defaut PLL configuration
            {
                const auto pll_error = _opal_kelly_front_panel.LoadDefaultPLLConfiguration();
                if (pll_error != okCFrontPanel::NoError) {
                    throw std::runtime_error(
                        "the default PLL configuration loading raised the error " + std::to_string(pll_error));
                }
            }

            // load the firmware
            {
                std::string firmware_filename = _parameter->get_string({"firmware"});
                std::ifstream firmware_file(firmware_filename);
                if (!firmware_file.good()) {
                    throw std::runtime_error(
                        "the firmware file '" + firmware_filename + "' does not exist or is not readable");
                }

                const auto firmware_error = _opal_kelly_front_panel.ConfigureFPGA(firmware_filename);
                if (firmware_error != okCFrontPanel::NoError) {
                    throw std::runtime_error(
                        "the firmware loading from file '" + firmware_filename + "' raised the error "
                        + std::to_string(firmware_error));
                }
            }

            // open the biases and selection settings
            _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 5, 1 << 5);
            _opal_kelly_front_panel.UpdateWireIns();

            // initialise the digital-to-analog converters (biases setup)
            for (const auto& category_pair : configuration()) {
                for (const auto& setting_pair : category_pair.second) {
                    _opal_kelly_front_panel.SetWireInValue(
                        0x01,
                        category_pair.first == "static" ?
                            setting_pair.second.at("value") :
                            static_cast<uint32_t>(_parameter->get_number({category_pair.first, setting_pair.first})));
                    _opal_kelly_front_panel.SetWireInValue(0x02, setting_pair.second.at("tension"));
                    _opal_kelly_front_panel.SetWireInValue(0x03, setting_pair.second.at("address"));
                    _opal_kelly_front_panel.UpdateWireIns();
                    _opal_kelly_front_panel.ActivateTriggerIn(0x40, 1);
                }
            }
            _opal_kelly_front_panel.ActivateTriggerIn(0x40, 6);

            // load the region of interest parameters
            if (_parameter->get_array_parameter({"columns_selection"}).size() > 0
                || _parameter->get_array_parameter({"rows_selection"}).size() > 0) {
                // compute the columns fill bits
                auto fill = std::vector<bool>();
                fill.reserve(544);
                if (_parameter->get_array_parameter({"columns_selection"}).size() > 0) {
                    auto state = _parameter->get_boolean({"select_first_column"});
                    auto first_pass = true;
                    while (fill.size() < 304) {
                        for (const auto& column_count : _parameter->get_array_parameter({"columns_selection"})) {
                            for (uint16_t index = 0; index < static_cast<uint16_t>(column_count->get_number({}));
                                 ++index) {
                                if (fill.size() >= 304) {
                                    if (first_pass) {
                                        throw std::runtime_error("The columns selection sum is larger than 304");
                                    } else {
                                        break;
                                    }
                                }
                                fill.push_back(state);
                            }
                            state = !state;
                        }
                        if (first_pass) {
                            first_pass = false;
                        }
                    }
                    std::reverse(fill.begin(), fill.end());
                } else {
                    fill = std::vector<bool>(304);
                }

                // compute the rows fill bits
                if (_parameter->get_array_parameter({"rows_selection"}).size() > 0) {
                    auto state = _parameter->get_boolean({"select_first_row"});
                    auto first_pass = true;
                    while (fill.size() < 544) {
                        for (const auto& column_count : _parameter->get_array_parameter({"rows_selection"})) {
                            for (uint16_t index = 0; index < static_cast<uint16_t>(column_count->get_number({}));
                                 ++index) {
                                if (fill.size() >= 544) {
                                    if (first_pass) {
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
                        if (first_pass) {
                            first_pass = false;
                        }
                    }
                    std::reverse(fill.begin() + 304, fill.end());
                } else {
                    auto fill_rows = std::vector<bool>(240);
                    fill.insert(fill.end(), fill_rows.begin(), fill_rows.end());
                }

                // pack the fill bits as 16 bits values for sending to the Opal Kelly
                uint16_t pack = 0;
                std::size_t pack_index = 0;

                for (auto fill_iterator = fill.begin(); fill_iterator != fill.end(); ++fill_iterator) {
                    if (*fill_iterator) {
                        pack &= ~(1 << pack_index);
                    } else {
                        pack |= 1 << pack_index;
                    }

                    if (pack_index == 15) {
                        _opal_kelly_front_panel.SetWireInValue(0x01, pack);
                        _opal_kelly_front_panel.SetWireInValue(
                            0x02, static_cast<uint32_t>((fill_iterator - fill.begin()) / 16));
                        _opal_kelly_front_panel.UpdateWireIns();
                        _opal_kelly_front_panel.ActivateTriggerIn(0x40, 3);
                        pack_index = 0;
                    } else {
                        ++pack_index;
                    }
                }
                _opal_kelly_front_panel.ActivateTriggerIn(0x40, 4);

                // define wether the pixels outside the selection are disabled, or wether the ones inside are
                _opal_kelly_front_panel.SetWireInValue(
                    0x00, _parameter->get_boolean({"selection_is_region_of_interest"}) ? 1 << 9 : 0, 1 << 9);
                _opal_kelly_front_panel.UpdateWireIns();

                // define which part of the pixels the selection is applied to
                if (_parameter->get_string({"apply_selection_to"}) == "change_detection"
                    || _parameter->get_string({"apply_selection_to"}) == "change_detection_and_exposure_measurement") {
                    _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 4, 1 << 4);
                    _opal_kelly_front_panel.UpdateWireIns();
                }
                if (_parameter->get_string({"apply_selection_to"}) == "exposure_measurement"
                    || _parameter->get_string({"apply_selection_to"}) == "change_detection_and_exposure_measurement") {
                    _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 3, 1 << 3);
                    _opal_kelly_front_panel.UpdateWireIns();
                }
            }

            // close the biases and selection settings
            _opal_kelly_front_panel.SetWireInValue(0x00, 0, 1 << 5);
            _opal_kelly_front_panel.UpdateWireIns();

            // load the exposure measurement trigger
            if (_parameter->get_string({"exposure_measurement_trigger"}) == "change_detection") {
                _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 0, 1 << 0);
                _opal_kelly_front_panel.UpdateWireIns();
            } else if (_parameter->get_string({"exposure_measurement_trigger"}) == "sequential") {
                _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 1, 1 << 1);
                _opal_kelly_front_panel.UpdateWireIns();

                if (_parameter->get_string({"apply_selection_to"}) == "change_detection"
                    || _parameter->get_string({"apply_selection_to"}) == "change_detection_and_exposure_measurement") {
                    _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 0, 1 << 0);
                    _opal_kelly_front_panel.UpdateWireIns();
                }
            }

            // reset the Atis FIFO
            _opal_kelly_front_panel.ActivateTriggerIn(0x40, 7);

            // reset the handlers
            _opal_kelly_front_panel.ActivateTriggerIn(0x40, 2);

            // enable periodic fake events
            if (_parameter->get_boolean({"send_fake_event_periodically"})) {
                _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 12, 1 << 12);
                _opal_kelly_front_panel.UpdateWireIns();
            }

            // start the FPGA events reading
            _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 10, 1 << 10);
            _opal_kelly_front_panel.UpdateWireIns();

            // start the reading loop
            _acquisition_loop = std::thread([this, serial]() -> void {
                try {
                    sepia::atis_event event;
                    std::vector<uint8_t> events_data((1 << 24) * 4);
                    std::vector<uint8_t> event_bytes(4);
                    while (_acquisition_running.load(std::memory_order_relaxed)) {
                        _opal_kelly_front_panel.UpdateWireOuts();
                        const auto number_of_events = (_opal_kelly_front_panel.GetWireOutValue(0x21) << 21)
                                                      + (_opal_kelly_front_panel.GetWireOutValue(0x20) << 5);
                        if (number_of_events > 1 << 24) {
                            if (_opal_kelly_front_panel.GetSerialNumber() == serial) {
                                throw std::runtime_error("Opal Kelly ATIS's FIFO overflow");
                            } else {
                                throw sepia::device_disconnected("Opal Kelly ATIS");
                            }
                        } else if (number_of_events > 0) {
                            _opal_kelly_front_panel.ReadFromPipeOut(0xa0, number_of_events * 4, events_data.data());
                            for (unsigned long event_index = 0; event_index < number_of_events; ++event_index) {
                                const auto events_data_iterator = events_data.begin() + 4 * event_index;
                                event_bytes.assign(events_data_iterator, events_data_iterator + 4);
                                if (event_bytes[3] < 240) {
                                    event.y = static_cast<uint16_t>(event_bytes[3]);
                                    event.x = ((static_cast<uint16_t>(event_bytes[1] & 0x20) << 3) | event_bytes[2]);
                                    if (event.x < 304) {
                                        event.t =
                                            _t_offset
                                            + ((static_cast<int64_t>(event_bytes[1] & 0x1f) << 8) | event_bytes[0]);
                                        event.is_threshold_crossing = (((event_bytes[1] & 0x40) >> 6) == 0x01);
                                        event.polarity = (((event_bytes[1] & 0x80) >> 7) == 0x01);
                                        event.y = 239 - event.y;
                                        if (!this->push(event)) {
                                            throw std::runtime_error("Computer's FIFO overflow");
                                        }
                                    }
                                } else if (
                                    event_bytes[3] == 240
                                    && ((static_cast<uint16_t>(event_bytes[1] & 0x20) << 3) | event_bytes[2]) == 305
                                    && ((static_cast<int64_t>(event_bytes[1] & 0x1f) << 8) | event_bytes[0])
                                           == 0x1555) {
                                    _t_offset += 0x2000;
                                }
                            }
                        } else {
                            if (_opal_kelly_front_panel.GetSerialNumber() != serial) {
                                throw sepia::device_disconnected("Opal Kelly ATIS");
                            }
                            std::this_thread::sleep_for(this->_sleep_duration);
                        }
                    }
                } catch (...) {
                    this->_handle_exception(std::current_exception());
                }
            });
        }
        specialized_camera(const specialized_camera&) = delete;
        specialized_camera(specialized_camera&&) = default;
        specialized_camera& operator=(const specialized_camera&) = delete;
        specialized_camera& operator=(specialized_camera&&) = default;
        virtual ~specialized_camera() {
            _acquisition_running.store(false, std::memory_order_relaxed);
            _acquisition_loop.join();
            if (_opal_kelly_front_panel.IsOpen()) {
                _opal_kelly_front_panel.Close();
            }
        }
        virtual void trigger() override {
            _opal_kelly_front_panel.SetWireInValue(0x00, 1 << 6, 1 << 6);
            _opal_kelly_front_panel.UpdateWireIns();
            _opal_kelly_front_panel.SetWireInValue(0x00, 0 << 6, 1 << 6);
            _opal_kelly_front_panel.UpdateWireIns();
        }

        protected:
        std::unique_ptr<sepia::parameter> _parameter;
        std::atomic_bool _acquisition_running;
        OpalKellyLegacy::okCFrontPanel _opal_kelly_front_panel;
        std::thread _acquisition_loop;
        uint64_t _t_offset;
    };

    /// make_camera creates a camera from functors.
    template <typename HandleEvent, typename HandleException>
    std::unique_ptr<specialized_camera<HandleEvent, HandleException>> make_camera(
        HandleEvent handle_event,
        HandleException handle_exception,
        std::unique_ptr<sepia::unvalidated_parameter> unvalidated_parameter =
            std::unique_ptr<sepia::unvalidated_parameter>(),
        std::size_t fifo_size = 1 << 24,
        std::string serial = std::string(),
        std::chrono::milliseconds sleep_duration = std::chrono::milliseconds(10)) {
        return sepia::make_unique<specialized_camera<HandleEvent, HandleException>>(
            std::forward<HandleEvent>(handle_event),
            std::forward<HandleException>(handle_exception),
            std::move(unvalidated_parameter),
            fifo_size,
            serial,
            sleep_duration);
    }
}
