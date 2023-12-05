#include <iostream>
#include <memory>
#include <vector>


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
        struct Patch{
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
        struct HybridModel : PhysicalModel {
            PHARE::core::Ions ions;
            std::string name() { return "HybridModel"; };
        };
    }
}

class WorkLoadEstimatorStrategy // ne connait pas SAMRAI
{
    public:
        WorkLoadEstimatorStrategy(std::string model_name, std::string workLoad_name) : strat_name{ model_name+"_"+ workLoad_name } { }
        auto name() { return strat_name; }
        virtual void estimate(double* wl, PHARE::core::Ions const& ions) = 0;
        //virtual void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) = 0;
    protected:
        std::string strat_name;
};


class ConcreteWorkLoadEstimatorStrategyHybridNPPC : public WorkLoadEstimatorStrategy // c'est lui seul qui sait comment faire
{
    public:
        ConcreteWorkLoadEstimatorStrategyHybridNPPC()
            : WorkLoadEstimatorStrategy("HybridModel", "NPPC") { }
        virtual void estimate(double* wl, PHARE::core::Ions const& ions) override { std::cout<<"estimator -> hybrid & nppc"<<std::endl; }
        //virtual void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) override { std::cout<<"estimator is  : nppc"<<std::endl; }
};


class WorkLoadEstimatorStrategyFactory
{
    public:
        static std::unique_ptr<WorkLoadEstimatorStrategy> create(PHARE::solver::PhysicalModel physical_model, std::string work_load_type_name)
        {
            if (physical_model.name() == "HybridModel" && work_load_type_name == "NPPC")
                return std::make_unique<ConcreteWorkLoadEstimatorStrategyHybridNPPC>();
            else return {};    
        }
};


class WorkLoadEstimator
{
    public:
        WorkLoadEstimator()
            : strat_{nullptr} { }
        void set_strategy(PHARE::solver::PhysicalModel physical_model, std::string work_load_type_name){
            strat_ = WorkLoadEstimatorStrategyFactory::create(physical_model, work_load_type_name);
        }
        auto strategy_name() { return strat_->name(); }
        //void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) { strat_->estimate(wl, ions); std::cout<<std::endl; }
        void estimate(double* wl, PHARE::core::Ions const& ions) {
            // loop sur les patch du level
            strat_->estimate(wl, ions);
            //strat_->estimate(level, hyb_model);
        }
        
        
    private:
        SAMRAI::tbox::Dimension dim_{2};
        std::unique_ptr<WorkLoadEstimatorStrategy> strat_;
        std::shared_ptr<SAMRAI::pdat::CellData> workLoad_;
        std::shared_ptr<SAMRAI::hier::CellVariable<double>> workLoadVariable_;
        std::string contextName_{"default"};
        std::shared_ptr<SAMRAI::hier::VariableContext> context_;
        SAMRAI::hier::IntVector gw0 = SAMRAI::hier::IntVector::getZero(dim_);
        //ID de la variable
};


namespace PHARE{
    namespace solver{
        struct MultiPhysicsIntegrator{
            MultiPhysicsIntegrator() : wle{ std::make_shared<WorkLoadEstimator>() } { wle->set_strategy(PHARE::solver::HybridModel(), "NPPC"); }

            std::shared_ptr<WorkLoadEstimator> wle;
            PHARE::core::Ions ions;
            PHARE::solver::HybridModel hm;
            double* wl;
            
            double advanceLevel(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level
                                //,std::shared_ptr<SAMRAI::hier::PatchHierarchy> const& hierarchy
                                )
            {
                
                
                wle->estimate(wl, ions);
                //hwle->estimate(level, hm);
                return 0;
            };
        };
    }
}


int main()
{
    //SAMRAI::tbox::Dimension dim(2);
    //nppc = std::make_shared<SAMRAI::pdat::CellVariable<int>>(dim, "nppc");
    //SAMRAI::hier::VariableDataBase* var_db = SAMRAI::hier::VariableDataBase::getDataBase();
    //SAMRAI::hier::IntVector gw0 = SAMRAI::hier::IntVector::getZero(dim);
    //std::shared_ptr<SAMRAI::hier::VariableContext> context_;
    //int nppc_id = var_db->registerVariableAndContext(nppc, , dim);

    //auto hwle = std::make_shared<HybridWorkLoadEstimator>();
    
    //hwle->set_strategy("nppc");
    //std::cout << "strategy name : " << hwle->strategy_name() << "\n";

    auto patchLevel = std::make_shared<SAMRAI::hier::PatchLevel>();





    PHARE::solver::MultiPhysicsIntegrator mpi;

    auto newTime = mpi.advanceLevel(patchLevel);
    (void)newTime;

    //for (auto p : patchLevel) { }
    //hwle->estimate();
    
    return 0;
}

