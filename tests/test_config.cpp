#include"sylar/log.h"
#include"sylar/config.h"
#include <yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_val_config = sylar::Config::Lookup("system.port",8080,"system port");
sylar::ConfigVar<std::vector<int>>::ptr g_vi_val_config =
sylar::Config::Lookup("system.vi",std::vector<int>({1,2}),"system.vi");
sylar::ConfigVar<std::list<int>>::ptr g_list_val_config =
sylar::Config::Lookup("system.list",std::list<int>({1,2}),"system.vi");
sylar::ConfigVar<std::set<int>>::ptr g_set_val_config =
sylar::Config::Lookup("system.set",std::set<int>({1,2}),"system.vi");
sylar::ConfigVar<std::unordered_set<int>>::ptr g_uset_val_config =
sylar::Config::Lookup("system.uset",std::unordered_set<int>({1,2}),"system.vi");
sylar::ConfigVar<std::map<std::string,int>>::ptr g_map_val_config =
sylar::Config::Lookup("system.map",std::map<std::string,int>{{"A",2},{"B",3}},"system.vi");
sylar::ConfigVar<std::unordered_map<std::string,int>>::ptr g_umap_val_config =
sylar::Config::Lookup("system.umap",std::unordered_map<std::string,int>{{"A",2},{"B",3}},"system.vi");

void print_yaml(const YAML::Node & node, int level){
    if(node.IsScalar()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<< node.Scalar() << " - "<<node.Type()<<" - "<<level;
    }else if(node.IsNull()){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<"NULL - "<<node.Type()<<" - "<<level;
    }else if(node.IsMap()){
        for(auto it=node.begin();it!=node.end();++it){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<it->first<<" - "<<it->second.Type()<<" - "<<level;
            print_yaml(it->second,level+1);
        }
    }else if(node.IsSequence()){
        for(size_t i = 0;i<node.size();++i){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<node[i]<<" - "<<node[i].Type()<<" - "<<level;
            print_yaml(node[i],level+1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log.yaml");
    print_yaml(root,0);

    // SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

void test_config()
{
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->toString();
    
#define XX(g_var,name,tip) \
    { \
        auto v= g_var->getValue();\
        for(auto &i :v) {\
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #tip " " #name <<": "<< i;\
        } \
    }

#define XX2(g_var,name,tip) \
    { \
        auto v= g_var->getValue();\
        for(auto &i :v) {\
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #tip " " #name <<": "<< "{ "\
            << i.first <<" - "<<i.second<<"}";\
        } \
    }

    XX(g_vi_val_config,vi,before)
    XX(g_list_val_config,list,before)
    XX(g_set_val_config,set,before)
    XX(g_uset_val_config,uset,before)
    XX2(g_map_val_config,map,before)
    XX2(g_umap_val_config,umap,before)

    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log.yaml");
    sylar::Config::LoadFromYaml(root);

    XX(g_vi_val_config,vi,after)
    XX(g_list_val_config,list,after)
    XX(g_set_val_config,set,after)
    XX(g_uset_val_config,uset,after)
    XX2(g_map_val_config,map,after)
    XX2(g_umap_val_config,umap,after)

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->toString();
}

int main(int argc,char ** argv){

    // test_yaml();
    test_config();
    return 0;
}