// clear; g++ -std=c++20 -O2 -Wall -pedantic -pthread main.cpp && ./a.out


#include <iostream>
#include <memory>
#include <vector>
#include <map>


namespace SAMRAI{
    namespace tbox{
        using Dimension = std::size_t;
    }
    namespace pdat{
        using CellData = std::vector<double>;
    }
    namespace hier{
        template<typename T>
        struct CellVariable{
        };
        struct VariableContext{
        };
        struct IntVector{
            static auto getZero(std::size_t dim) { return SAMRAI::hier::IntVector(); };
        };
        struct PatchData {
        };
        struct Patch{
            std::shared_ptr<PatchData> getPatchData (const int id) const { return std::make_shared<PatchData>(); };
        };
        using PatchLevel = std::vector<Patch>;
        using PatchHierarchy = std::vector<PatchLevel>;
    }
}


namespace PHARE{
    namespace core{
        struct Ions{
            using field_type = double;
            Ions() : rho_{nullptr} { };

            field_type* rho_{nullptr};

            field_type& density() { return *rho_; };
        };
    }
    namespace solver{
        struct PhysicalModel {
            virtual std::string name() = 0;
        };
        struct HybridModel : public PhysicalModel {
            PHARE::core::Ions ions;
            std::string name() { return "HybridModel"; };
        };
    }
}


class WorkLoadEstimator
{
    public:
        WorkLoadEstimator() { }

        virtual void estimate(SAMRAI::hier::PatchLevel lev, double*, PHARE::core::Ions const&) = 0;
        virtual void set_strategy(std::string) = 0;
        int getID() { return id_; };

    private:
        SAMRAI::tbox::Dimension dim_{2};
        std::shared_ptr<SAMRAI::pdat::CellData> workLoad_;
        std::shared_ptr<SAMRAI::hier::CellVariable<double>> workLoadVariable_;
        std::string contextName_{"default"};
        std::shared_ptr<SAMRAI::hier::VariableContext> context_;
        SAMRAI::hier::IntVector gw0 = SAMRAI::hier::IntVector::getZero(dim_);
        int const id_{12};
};


class HybridWorkLoadEstimatorStrategy
{

};


class ConcreteHybridWorkLoadEstimatorStrategyNPPC : public HybridWorkLoadEstimatorStrategy
{
    public :
        void estimate(double* wl, PHARE::core::Ions const& ions) { } ;
};


class HybridWorkLoadStrategyFactory
{
    public :
        static std::unique_ptr<HybridWorkLoadEstimatorStrategy> create(std::string stratName)
            {
                if (stratName == "NPPC")
                    return std::make_unique<ConcreteHybridWorkLoadEstimatorStrategyNPPC>();
                else
                    return {};
            };
};


class HybridWorkLoadEstimator : public WorkLoadEstimator
{
    public :
        virtual void estimate(SAMRAI::hier::PatchLevel levels, double* wl, PHARE::core::Ions const& ions)
        {
            for (auto& p : levels)
            {
                auto pd = p.getPatchData(this->getID());



                // TODO



            }
        };
        virtual void set_strategy(std::string stratName)
        {
            strat_ = HybridWorkLoadStrategyFactory::create(stratName);
        };
    private:
        std::unique_ptr<HybridWorkLoadEstimatorStrategy> strat_;
};


class WorkLoadEstimatorFactory
{
    public :
        static std::shared_ptr<WorkLoadEstimator> create(std::string modelName)
        {
            if (modelName == "HybridModel")
                return std::make_shared<HybridWorkLoadEstimator>();
            else
                return {};
        }
};




namespace PHARE{
    namespace solver{
        struct MultiPhysicsIntegrator{
            //MultiPhysicsIntegrator() : wle{ std::make_shared<WorkLoadEstimator>() } { wle->set_strategy(PHARE::solver::HybridModel()); }
            MultiPhysicsIntegrator(std::string modelName) : wle{ WorkLoadEstimatorFactory::create(modelName) } {
                pm = (modelName == "HybridModel") ? std::make_shared<PHARE::solver::HybridModel>() : nullptr;
            }

            std::shared_ptr<WorkLoadEstimator> wle;
            PHARE::core::Ions ions;
            std::shared_ptr<PHARE::solver::PhysicalModel> pm;
            double* wl;

            double advanceLevel(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level)
            {
                std::cout << pm->name() << std::endl;
                //wle->estimate(level, wl, ions);
                return 0;
            };
        };
    }
}


int main()
{
    auto patchLevel = std::make_shared<SAMRAI::hier::PatchLevel>();

    PHARE::solver::MultiPhysicsIntegrator mpi("HybridModel");

    auto newTime = mpi.advanceLevel(patchLevel);
    (void)newTime;

    return 0;
}

