#include"sylar/log.h"
#include"sylar/config.h"
#include <yaml-cpp/yaml.h>

sylar::ConfigVar<int>::ptr g_int_val_config = sylar::Config::Lookup("syatem.port",8080,"system port");

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

    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log.yaml");
    sylar::Config::LoadFromYaml(root);

    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->getValue();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << g_int_val_config ->toString();
}

int main(int argc,char ** argv){

    // test_yaml();
    test_config();
    return 0;
}