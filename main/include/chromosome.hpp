#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <limits>
#include <string>

using namespace cadmium;
using namespace std;

template<typename TIME>
struct Chromosome {

    //Ports
    struct phase_in : public in_port<string> {};
    struct status_out : public out_port<string> {};

    using input_ports = tuple<phase_in>;
    using output_ports = tuple<status_out>;

    //State 
    struct state_type {
        string state;
        bool output_pending;
    };
    state_type state;

    Chromosome() {
        state.state = "uncondensed";
        state.output_pending = false;
    }

    void external_transition(TIME e,
    typename make_message_bags<input_ports>::type mbs){

        for (const auto &x: get_messages<phase_in>(mbs)){
            if (x == "Interphase"){
                state.state = "uncondensed";
            }
            else if (x == "Prophase"){
                state.state = "condensed";
            }
            else if (x == "Metaphase"){
                state.state = "aligned";
            }
            else if (x == "Anaphase"){
                state.state = "separating";
            }
            else if (x == "Telophase"){
                state.state = "decondensing";
            }
            else if (x == "Cytokinesis"){
                state.state = "completed";
            }
            state.output_pending = true;
        }
    }

    void internal_transition(){
        state.output_pending = false;
    }

    typename make_message_bags<output_ports>::type output() const{
        typename make_message_bags<output_ports>::type bags;
        if (state.state == "completed"){
            get_messages<status_out>(bags).push_back("ready");
        } else{
            get_messages<status_out>(bags).push_back("not_ready");
        }
        return bags;
    }

    TIME time_advance() const{
        if (state.output_pending){
            return TIME(0);
        }
        return std::numeric_limits<TIME>::infinity();
    }
};

#endif