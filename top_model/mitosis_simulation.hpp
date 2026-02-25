#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include "../main/include/cell_structures.hpp"
#include "../main/include/status_checker.hpp"


class MitosisSimulation : public Coupled {
public:
    MitosisSimulation(const std::string& id) : Coupled(id) {
        auto structures = addComponent<CellStructures>("structures");
        auto checker    = addComponent<StatusChecker>("checker");

        // Direct coupling between the bundled container and the checker
        addCoupling(structures->out_chrom,  checker->in_chrom);
        addCoupling(structures->out_ne,     checker->in_ne);
        addCoupling(structures->out_sp,     checker->in_sp);
        addCoupling(structures->out_cen,    checker->in_cen);
        addCoupling(structures->out_nucleo, checker->in_nucleo);
    }
};