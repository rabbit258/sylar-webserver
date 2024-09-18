#include"sylar/log.h"
#include"sylar/config.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

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

class Person{
public:
    std::string m_name;
    int m_age;
    int m_sex;

    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name="<< m_name
        << " age="<<m_age
        << " sex="<<m_sex << "]";
        return ss.str();
    }

    bool operator==(const Person & oth)const {
        return m_name==oth.m_name &&
                m_age==oth.m_age &&
                m_sex==oth.m_sex;
    }
};

sylar::ConfigVar<Person>::ptr g_person =
    sylar::Config::Lookup("class.person",Person(),"system person");
sylar::ConfigVar<std::map<std::string,std::vector<Person>>>::ptr g_mv_person =
    sylar::Config::Lookup("class.vec_map",std::map<std::string,std::vector<Person>>(),"system person");

namespace sylar{
template<>
class LexicalCast<std::string,Person> {
public:
    Person operator()(const std::string & v){
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person,std::string> {
public:
    std::string operator()(const Person & p){
        YAML::Node node ;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};
}

void test_class(){
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<"before "<< g_person->getValue().toString() << " - "<<g_person->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before "<< g_mv_person->toString();
    g_person->addListener(10,[](const Person & s,const Person & t){
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT())<<"old value :" << s.toString() <<
        "new value :"<<t.toString(); 
    });


    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log.yaml");
    sylar::Config::LoadFromYaml(root);



    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after "<< g_mv_person->toString();
    SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<"after "<< g_person->getValue().toString() << " - "<<g_person->toString();
}

void test_log()
{
    static sylar::Logger::ptr system_log = SYLAR_LOG_NAME("system");
    SYLAR_LOG_INFO(system_log) << "hello system" << std::endl;
    std::cout<< sylar::LoggerMgr::GetInstance()->toYamlString() <<std::endl;
    
    YAML::Node root = YAML::LoadFile("/home/fyx/sylar/bin/conf/log.yaml");
    sylar::Config::LoadFromYaml(root);

    std::cout<< "====================\n";
    std::cout<< sylar::LoggerMgr::GetInstance()->toYamlString() <<std::endl;
    std::cout<< "====================\n";

    SYLAR_LOG_INFO(system_log) << "hello system" << std::endl;

    system_log->setFormatter("%d - %m%n");
    SYLAR_LOG_INFO(system_log) << "hello system" << std::endl;
}
int main(int argc,char ** argv){

    // test_yaml();
    // test_config();
    // test_class();
    test_log();
    return 0;
}