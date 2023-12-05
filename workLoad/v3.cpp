#include <iostream>
#include <memory>
#include <vector>

class HybridWorkLoadEstimatorStrategy
{
    public:
        HybridWorkLoadEstimatorStrategy(std::string name) : strat_name{ name } { }
        auto name() { return strat_name; }
        virtual void estimate() = 0;
    protected:
        std::string strat_name;
};

class ConcreteHybridWorkLoadEstimatorStrategy_NPPC : public HybridWorkLoadEstimatorStrategy
{
    public:
        ConcreteHybridWorkLoadEstimatorStrategy_NPPC()
            : HybridWorkLoadEstimatorStrategy( "nppc" ) { }
        virtual void estimate() override { std::cout<<"i am the nppc estimator"<<std::endl; }
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


class HybridWorkLoadEstimator final
{
    public:
        HybridWorkLoadEstimator()
            : strat_{nullptr} { }
        void set_strategy(std::string strategy_name){ strat_ = HybridWorkLoadEstimatorStrategyFactory::create(strategy_name); }
        auto strategy_name() { return strat_->name(); }
        void estimate() { strat_->estimate(); };
        
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
            
            double advanceLevel(std::shared_ptr<SAMRAI::hier::PatchLevel> const& level
                                //,std::shared_ptr<SAMRAI::hier::PatchHierarchy> const& hierarchy
                                )
            {
                hwle->estimate();
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

    //for (auto p : patchLevel) { }
    //hwle->estimate();
    
    return 0;
}

