#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgEarth/GeoTransform>
#include <osg/Billboard>

#include <iostream>
#include <type_traits>
#include <typeindex>
#include <map>

class FindNodeTypes : public osg::NodeVisitor
{
public:

    std::set<std::type_index> types;
    std::map<std::type_index, std::set<osg::ref_ptr<osg::Node>>> found;

    FindNodeTypes():
        osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {}

    void apply(osg::Node& node)
    {
        if (types.count(typeid(node)) != 0)
        {
            found[typeid(node)].insert(&node);
        }
        traverse(node);
    }
};

class FindAllNodes : public osg::NodeVisitor
{
public:

    std::map<std::type_index, std::set<osg::ref_ptr<osg::Node>>> found;

    FindAllNodes():
        osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {}

    void apply(osg::Node& node)
    {
        found[typeid(node)].insert(&node);

        traverse(node);
    }
};

#define COMPIULE_WITH_GEOTRANSFORM 0

int main( int argc, char **argv )
{
    // use an ArgumentParser object to manage the program arguments.
    osg::ArgumentParser arguments(&argc,argv);

    osg::ref_ptr<osg::Group> group = new osg::Group;

    bool useGeotransform = false;

#if COMPIULE_WITH_GEOTRANSFORM
    if (useGeotransform)
    {
        group->addChild(new osgEarth::GeoTransform());
    }
#endif

    for(int pos=1; pos < arguments.argc()-1; ++pos)
    {
        std::cout<<"command line : "<<arguments[pos]<<std ::endl;

        auto model = osgDB::readRefNodeFile(arguments[pos]);
        if (model.valid()) group->addChild(model);
    }

    if (group->getNumChildren()==0)
    {
        std::cout<<"No data loaded."<<std::endl;
        return 0;
    }

#if 0
    {
        FindNodeTypes findNodeTypes;
        findNodeTypes.types.insert(typeid(osg::Group));
        findNodeTypes.types.insert(typeid(osg::Billboard));
        findNodeTypes.types.insert(typeid(osg::Geode));

        group->accept(findNodeTypes);

        std::cout<<"FoundNodetypes "<<std::endl;
        for(auto& [type, nodes] : findNodeTypes.found)
        {
            std::cout<<"type = "<<type.name()<<", nodes.size() "<<nodes.size()<<std::endl;
        }
    }
#endif

    {
        FindAllNodes findNodes;

        group->accept(findNodes);

        std::cout<<"\nFoundAllNodes "<<std::endl;
        for(auto& [type, nodes] : findNodes.found)
        {
            std::cout<<"type = "<<type.name()<<", nodes.size() "<<nodes.size()<<std::endl;
        }

        auto itr = findNodes.found.find(typeid(osg::Group));
        if (itr != findNodes.found.end())
        {
            std::cout<<"itr->first = "<<itr->first.name()<<std::endl;
        }

#if COMPIULE_WITH_GEOTRANSFORM
        if (useGeotransform)
        {
            auto& geoTransforms = findNodes.found[typeid(osgEarth::GeoTransform)];
            for(auto& geoTransform : geoTransforms)
            {

            }
        }
#endif

    }

    osg::ref_ptr<osg::Node> root;
    if (group->getNumChildren()==1) root = group->getChild(0);
    else root = group;

    osgDB::writeNodeFile(*root, arguments[arguments.argc()-1]);

}
