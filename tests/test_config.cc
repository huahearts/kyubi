#include "kyubi/config.h"
#include "kyubi/log.h"
#include <yaml-cpp/yaml.h>

kyubi::ConfigVar<int>::ptr g_int_value_config = 
    kyubi::Config::Lookup("system.port",(int)8080,"ststem port");

kyubi::ConfigVar<float>::ptr g_float_value_config = 
    kyubi::Config::Lookup("system.value",(float)10.2f,"ststem value");

kyubi::ConfigVar<std::vector<int> >::ptr g_vector_value_config = 
    kyubi::Config::Lookup("system.int_vec",std::vector<int>{1,2},"system int vector");

kyubi::ConfigVar<std::list<int> >::ptr g_list_value_config = 
    kyubi::Config::Lookup("system.int_list",std::list<int>{1,2},"system int list");

kyubi::ConfigVar<std::set<int> >::ptr g_set_value_config = 
    kyubi::Config::Lookup("system.int_set",std::set<int>{1,2},"system int set");

kyubi::ConfigVar<std::unordered_set<int> >::ptr g_uset_value_config = 
    kyubi::Config::Lookup("system.int_unordered_set",std::unordered_set<int>{1,2},"system int unordered_set");

kyubi::ConfigVar<std::map<std::string,int> >::ptr g_map_value_config = 
    kyubi::Config::Lookup("system.int_map",std::map<std::string,int>{{"k",2}},"system str int map");

void print_yaml(const YAML::Node& node,int level) {
    if(node.IsScalar())
    {
        KYUBI_LOG_INFO(KYUBI_LOG_ROOT())<< std::string(level * 4,' ') << node.Scalar() << node.Type() << " - "<< level;
    } else if(node.IsNull()){
        KYUBI_LOG_INFO(KYUBI_LOG_ROOT())<< std::string(level * 4, ' ') << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for( auto it = node.begin();it != node.end();++it) {
            KYUBI_LOG_INFO(KYUBI_LOG_ROOT())<< std::string(level * 4, ' ') << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second,level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0;i < node.size();++i) {
            KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i],level + 1);
        }
    }
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/log.yml");
    print_yaml(root,0);
   // KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << root;
}

void test_config() {
    KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << g_int_value_config->getValue();
    KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << g_float_value_config->toString();
#define XX_M(g_var, name,prefix) \
    {\
        auto& v = g_var->getValue();\
        for(auto& i : v) { \
            KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << #prefix " " #name ": {" \
                << i.first << " - " << i.second << "}";\
        } \
        KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

#define XX(g_var, name,prefix) \
    {\
        auto& v = g_var->getValue();\
        for(auto& i : v) { \
            KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << #prefix " " #name ": " << i; \
        } \
        KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }
    XX(g_vector_value_config,int_vec,before)
    XX(g_list_value_config,int_list,before)
    XX(g_set_value_config,int_set,before)
    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/log.yml");
    kyubi::Config::LoadFromYaml(root);
    KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << g_int_value_config->getValue();
    KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << g_float_value_config->toString();
    XX(g_vector_value_config,int_vec,after)
    XX(g_list_value_config,int_list,after)
    XX(g_set_value_config,int_set,after)
    XX_M(g_map_value_config,int_map,after)
}

int main(int argc,char** argv){
    test_config();
    return 0;
}