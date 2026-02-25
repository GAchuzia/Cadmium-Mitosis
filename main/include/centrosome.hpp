#ifndef CENTROSOME_HPP
#define CENTROSOME_HPP

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <limits>
#include <string>

using namespace cadmium;
using namespace std;

struct Centrosome {

    //Ports
    struct phase_in : public in_port<string> {};
    struct status_out : public out_port<string> {};

    using input_ports = tuple<phase_in>;
    using output_ports = tuple<status_out>;

    //State 
    struct state_type {
        string state;
    };

    state_type state;

    Centrosome() {
        state.state = "duplicated"; 
    }

    // Internal Transition


    // External Transition
    void external_transition(TIME e,
        typename make_message_bags<input_ports>::type mbs) {

        for (const auto &x : get_messages<phase_in>(mbs)) {

            if (x == "Interphase") {
                state.state = "duplicated";
            }
            else if (x == "Prophase") {
                state.state = "separating";
            }
            else if (x == "Metaphase") {
                state.state = "aligned";
            }
            else if (x == "Anaphase") {
                state.state = "separated";
            }
            else if (x == "Telophase") {
                state.state = "stable";
            }
            else if (x == "Cytokinesis") {
                state.state = "stable";
            }
        }
    }

    TIME time_advance() const {

    }

};