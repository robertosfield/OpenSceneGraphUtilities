#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <iostream>

int main( int argc, char **argv )
{
    // use an ArgumentParser object to manage the program arguments.
    osg::ArgumentParser arguments(&argc,argv);

    osg::ref_ptr<osg::Group> group = new osg::Group;

    for(int pos=1; pos < arguments.argc()-1; ++pos)
    {
        std::cout<<"command line : "<<arguments[pos]<<std::endl;

        auto model = osgDB::readRefNodeFile(arguments[pos]);
        if (model.valid()) group->addChild(model);
    }

    if (group->getNumChildren()==0)
    {
        std::cout<<"No data loaded."<<std::endl;
        return 0;
    }

    osg::ref_ptr<osg::Node> root;
    if (group->getNumChildren()==1) root = group->getChild(0);
    else root = group;

    osgDB::writeNodeFile(*root, arguments[arguments.argc()-1]);

}
