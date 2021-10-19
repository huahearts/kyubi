#include "kyubi/config.h"
#include "kyubi/log.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

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
    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/test.yml");
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

class Person{
public:
    Person() = default;
public:
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;
    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name = " << m_name 
        << " Age = " << m_age
        << " Sex = " << m_sex
        << "]";
        return ss.str();
    }
    bool operator==(const Person& oth) const {
        return m_name == oth.m_name 
            && m_age ==oth.m_age 
            && m_sex == oth.m_sex;
    }
};

namespace kyubi {
template<>
class LexicalCast<std::string,Person> {
public:
    Person operator() (const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<> 
class LexicalCast<Person,std::string > {
public:
    std::string operator() (const Person& p) {
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

}

kyubi::ConfigVar<Person>::ptr g_person = 
    kyubi::Config::Lookup("class.person",Person(),"system person");
kyubi::ConfigVar<std::map<std::string,Person> >::ptr g_person_map = 
    kyubi::Config::Lookup("class.map",std::map<std::string,Person>(),"system person");

kyubi::ConfigVar<std::map<std::string,std::vector<Person> > >::ptr g_person_vec_map = 
    kyubi::Config::Lookup("class.vec_map",std::map<std::string,std::vector<Person>>(),"system vec person");
void test_class() {
    //KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << "before:"<<g_person->getValue().toString() << " - " << g_person->toString();
#define XX_PM(g_var,prefix)\
    {\
        auto m = g_var->getValue();\
        for(auto& i:m) {\
            KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << #prefix " - " << i.first << " - "\
            << i.second.toString();\
        }\
        KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << prefix<<": size=" << m.size();\
    }

    g_person->addListener([](const Person& old_val,const Person& new_val){
         KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << "old_value = " << old_val.toString()
            << "new_value = " << new_val.toString();
    });
    XX_PM(g_person_map,"class.map before")
    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/test.yml");
    kyubi::Config::LoadFromYaml(root);
    XX_PM(g_person_map,"class.map after")
    KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << "after:"<<g_person_vec_map->toString();
    //KYUBI_LOG_INFO(KYUBI_LOG_ROOT()) << "after:"<<g_person->getValue().toString() << " - " << g_person->toString();
}

void test_log() {
    static kyubi::Logger::ptr system_log = KYUBI_LOG_NAME("system");
    KYUBI_LOG_INFO(system_log) << "hello system" << std::endl;
    std::cout << kyubi::LogMgr::GetInstance()->toYamlString() << std::endl;
    YAML::Node root = YAML::LoadFile("/root/workspace/kyubi/bin/conf/log.yml");
    kyubi::Config::LoadFromYaml(root);
    std::cout << kyubi::LogMgr::GetInstance()->toYamlString() << std::endl;
    std::cout << root << std::endl;
    system_log->setFormatter("%d - %m%n");
    KYUBI_LOG_INFO(system_log) << "hello system" << std::endl;

}

int main(int argc,char** argv){
    //test_config();
    //test_class();
    test_log();
    return 0;
}
