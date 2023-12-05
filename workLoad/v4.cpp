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
            int a=444;
        };
    }
    namespace solver{
        struct HybridModel {
            PHARE::core::Ions ions;
        };
    }
}

class HybridWorkLoadEstimatorStrategy
{
    public:
        HybridWorkLoadEstimatorStrategy(std::string name) : strat_name{ name } { }
        auto name() { return strat_name; }
        //virtual void estimate(double* wl, PHARE::core::Ions const& ions) = 0;
        virtual void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) = 0;
    protected:
        std::string strat_name;
};


class ConcreteHybridWorkLoadEstimatorStrategy_NPPC : public HybridWorkLoadEstimatorStrategy
{
    public:
        ConcreteHybridWorkLoadEstimatorStrategy_NPPC()
            : HybridWorkLoadEstimatorStrategy( "nppc" ) { }
        //virtual void estimate(double* wl, PHARE::core::Ions const& ions) override { std::cout<<"estimator is  : nppc"<<std::endl; }
        virtual void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) override { std::cout<<"estimator is  : nppc"<<std::endl; }
};


class HybridWorkLoadEstimatorStrategyFactory
{
    public:
        static std::unique_ptr<HybridWorkLoadEstimatorStrategy> create(std::string name)
        {
            if (name == "nppc")
                return std::make_unique<ConcreteHybridWorkLoadEstimatorStrategy_NPPC>();
            else return {};    
        }
};


class HybridWorkLoadEstimator
{
    public:
        HybridWorkLoadEstimator()
            : strat_{nullptr} { }
        void set_strategy(std::string strategy_name){ strat_ = HybridWorkLoadEstimatorStrategyFactory::create(strategy_name); }
        auto strategy_name() { return strat_->name(); }
        //void estimate(double* wl, PHARE::core::Ions const& ions) { strat_->estimate(wl, ions); std::cout<<std::endl; }
        void estimate(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level, PHARE::solver::HybridModel hyb_model) { strat_->estimate(level, hyb_model); std::cout<<std::endl; }
        
        
    private:
        SAMRAI::tbox::Dimension dim_{2};
        std::unique_ptr<HybridWorkLoadEstimatorStrategy> strat_;
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
            MultiPhysicsIntegrator() : hwle{ std::make_shared<HybridWorkLoadEstimator>() } { hwle->set_strategy("nppc"); }

            std::shared_ptr<HybridWorkLoadEstimator> hwle;
            PHARE::core::Ions ions;
            PHARE::solver::HybridModel hm;
            double* wl;
            
            double advanceLevel(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level
                                //,std::shared_ptr<SAMRAI::hier::PatchHierarchy> const& hierarchy
                                )
            {
                //hwle->estimate(wl, ions);
                hwle->estimate(level, hm);
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

    auto hwle = std::make_shared<HybridWorkLoadEstimator>();
    
    hwle->set_strategy("nppc");
    std::cout << "strategy name : " << hwle->strategy_name() << "\n";

    auto patchLevel = std::make_shared<SAMRAI::hier::PatchLevel>();

    PHARE::solver::MultiPhysicsIntegrator mpi;

    auto newTime = mpi.advanceLevel(patchLevel);
    (void)newTime;

    //for (auto p : patchLevel) { }
    //hwle->estimate();
    
    return 0;
}

