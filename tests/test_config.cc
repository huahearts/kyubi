#include "kyubi/config.h"
#include "kyubi/log.h"
#include <yaml-cpp/yaml.h>

kyubi::ConfigVar<int>::ptr g_int_value_config = 
    kyubi::Config::Lookup("system.port",(int)8080,"ststem port");

kyubi::ConfigVar<float>::ptr g_float_value_config = 
    kyubi::Config::Lookup("system.value",(float)10.2f,"ststem value");

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

    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/log.yml");
    kyubi::Config::LoadFromYaml(root);
}

int main(int argc,char** argv){
    test_config();
    return 0;
}