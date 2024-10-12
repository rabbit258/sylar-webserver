#include "config.h"
#include <iostream>
namespace sylar{
    // Config::ConfigVarMap Config::m_datas;

/// @brief 解析出yaml文件中的每个属性，存在output里
/// @param prefix 当前属性名的前缀
/// @param node 当前层的node
/// @param output 引用输出
static void ListAllMember(const std::string & prefix,
                          const YAML::Node & node,
                          std::list<std::pair<std::string,const YAML::Node>> & output){
    if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789")
        !=std::string::npos){
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())<< "Config invalid name: "<< prefix <<" : "<<node;
            return;
    }
    output.push_back(std::make_pair(prefix,node));
    if(node.IsMap()){
        for(auto it=node.begin();it!=node.end();++it){
            ListAllMember(prefix.empty()?it->first.Scalar():
            prefix+"."+it->first.Scalar(),it->second,output);
        }
    }
}
void Config::LoadFromYaml(const YAML::Node &node)
{
    std::list<std::pair<std::string,const YAML::Node>> all_nodes;
    ListAllMember("",node,all_nodes);

    for(auto & i:all_nodes){
        std::string key=i.first;
        if(key.empty()){
            continue;
        }

        std::transform(key.begin(),key.end(),key.begin(),::tolower);
        //查看是否已经存在该属性
        ConfigVarBase::ptr var = LookupBase(key);
        if(var){
            if(i.second.IsScalar()){
                var->fromString(i.second.Scalar());
            }
            else {
                std::stringstream ss;
                ss << i.second;
                var->fromString(ss.str());
            }
        }
    }
}
ConfigVarBase::ptr Config::LookupBase(const std::string &name)
{
    RWMutexType::ReadLock lock(GetMutex());
    auto it = GetDatas().find(name);
    return it==GetDatas().end()?nullptr:it->second;
}
void Config::Visit(std::function<void(ConfigVarBase::ptr)> cb)
{
    RWMutexType::ReadLock lock(GetMutex());
    ConfigVarMap & m = GetDatas();
    for(auto it = m.begin();it != m.end();++it){
        cb(it->second);
    }
}
}