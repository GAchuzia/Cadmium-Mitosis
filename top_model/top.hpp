#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include "../main/include/centrosome.hpp"
#include "../main/include/chromosome.hpp"
#include "../main/include/nuclear_envelope.hpp"
#include "../main/include/nucleolus.hpp"

using namespace cadmium;

class top_model : public Coupled {
public:
    top_model(const std::string& id) : Coupled(id) {
        // Test 1: Centrosome
        auto input_reader_centrosome = addComponent<lib::IEStream<std::string>>("reader_Centrosome", "input_data/atomic_models/TC_Centrosome1.txt");
        auto centrosome = addComponent<Centrosome>("Centrosome_Test");
        addCoupling(input_reader_centrosome->out, centrosome->phase_in);

        // Test 2: Nucleolus
        auto input_reader_nucleolus = addComponent<lib::IEStream<std::string>>("reader_Nucleolus", "input_data/atomic_models/TC_Nucleolus1.txt");
        auto nucleolus = addComponent<Nucleolus>("Nucleolus_Test");
        addCoupling(input_reader_nucleolus->out, nucleolus->phase_in);

        // Chromosome TC-C1/TC-C2 (full progression)
        auto input_reader_chromosome_1 = addComponent<lib::IEStream<std::string>>("reader_Chromosome1", "input_data/atomic_models/TC_Chromosome1.txt");
        auto chromosome_1 = addComponent<Chromosome>("Chromosome_TC1_TC2");
        addCoupling(input_reader_chromosome_1->out, chromosome_1->phase_in);

        // Chromosome TC-C3 (invalid jump)
        auto input_reader_chromosome_2 = addComponent<lib::IEStream<std::string>>("reader_Chromosome2", "input_data/atomic_models/TC_Chromosome2.txt");
        auto chromosome_2 = addComponent<Chromosome>("Chromosome_TC3_InvalidJump");
        addCoupling(input_reader_chromosome_2->out, chromosome_2->phase_in);

        // Nuclear Envelope TC-NE1 (Prophase)
        auto input_reader_ne_1 = addComponent<lib::IEStream<std::string>>("reader_NE1", "input_data/atomic_models/TC_Nuclear_Envelope1.txt");
        auto nuclear_envelope_1 = addComponent<NuclearEnvelope>("NuclearEnvelope_TC1_Prophase");
        addCoupling(input_reader_ne_1->out, nuclear_envelope_1->phase_in);

        // Nuclear Envelope TC-NE2 (Telophase)
        auto input_reader_ne_2 = addComponent<lib::IEStream<std::string>>("reader_NE2", "input_data/atomic_models/TC_Nuclear_Envelope2.txt");
        auto nuclear_envelope_2 = addComponent<NuclearEnvelope>("NuclearEnvelope_TC2_Telophase");
        addCoupling(input_reader_ne_2->out, nuclear_envelope_2->phase_in);
    }
};
