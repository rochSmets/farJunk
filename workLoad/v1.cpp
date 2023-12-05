#include <iostream>
#include <memory>
#include <vector>

class HybridWorkLoadEstimatorStrategy
{
    public:
        HybridWorkLoadEstimatorStrategy(std::string name) : strat_name{ name } { }
        auto name() { return strat_name; }
    protected:
        std::string strat_name;
};

class ConcreteHybridWorkLoadEstimatorStrategy_NPPC : public HybridWorkLoadEstimatorStrategy
{
    public:
        ConcreteHybridWorkLoadEstimatorStrategy_NPPC()
            : HybridWorkLoadEstimatorStrategy( "nppc" ) { }
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

class HybridWorkLoadEstimator final
{
    public:
        HybridWorkLoadEstimator()
            : strat_{nullptr} { }
        void set_strategy(std::string strategy_name){ strat_ = HybridWorkLoadEstimatorStrategyFactory::create(strategy_name); }
        auto strategy_name() { return strat_->name(); }
        
    private:
        std::unique_ptr<HybridWorkLoadEstimatorStrategy> strat_;
        std::vector<int> cellData;
};


struct patch {};
using patchLevel = std::vector<patch>;


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
    
    //for (auto p : patchLevel) { }
    //hwle->estimate();
    
    return 0;
}

