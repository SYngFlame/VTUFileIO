# VTKFileIO详细设计
## Export导出详细设计
模块的功能包括： 
+ 菜单栏按钮插入，在`VTKFileIOToolset`实现：

```cpp
//VTKFileIOToolset.cpp

SAMMenuCommand* exportVTKCmd = new SAMMenuCommand(this, fileMenu, tr("&VTK Legacy.."));
testMenu->addAction(exportVTKCmd);
```

+ 读取模型树，定位所有模型数据位置。在`VTKFileManager`实现：

``` cpp
int VTUFileManager::Init(basMdb* mdb) {
	cowListString modelList;
	QVector<QString> model_parts;
	for (int i = 0; i < modelList.Length(); ++i) {
		const ptoKPartRepository& parts;
		for (int p = 1; p <= parts.Size(); ++p) {
			QString partname = parts.GetKey(p);
			model_parts.append(partname);
		}
		SAMparts.append(model_parts);
	}
	return 0;
};
```
+ 读取场景(**Part**、**Assembly**、**Visualization**),确定数据输出范围。在不同视图下输出VTK文件包含的内容如下表：

    |场景|输出范围|
    |:--------|:--------|
    |**Part**|**Part**|
    |**Assembly**|所有**Part**|
    |**Visualization**|所有**Part** + 后处理数据|

```cpp
//SAMVTKFileIOFragment.cpp

class omuPrimtive;
omuPrimtive SAMSceneMethod::method{
    {"Part",VTKFileManager::ReadPart},
    {"Assembly",VTKFileManager::ReadAllParts},
    {"Visualization",VTKFileManager::ReadAll}
}
```
+ 读取点和单元数据:
```cpp
int SAMVTKFileIOFragment::ReadNode(){
    ftrFeatureList* flpart = part.GetFeatureList();
    const bmeMesh* objectMesh = flpart->ConstGetMesh(bdoDefaultInstId);

const bmeNodeData& nodeData = objectMesh->NodeData();
}

//VTKElementHandler.cpp

//TODO
```
+ VTK文件写出:
```cpp
//TODO
```

## Import导入详细设计
