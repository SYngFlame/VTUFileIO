# 二次开发接口使用说明

### 文档编写说明

此文档记录了开发过程中使用的大部分 SAM 二次开发接口。

部分在使用中查找到的接口依赖库 (可能不准确) 会以 *调用库：**SAMLib.lib*** 的形式附加在头文件下。

文档忽略 **inline** 修饰符，包含 **static**、**const** 修饰符

文档中类型和对象使用样式规则为:

- 实例化的对象：*SAMObject*

- 类型名：`SAMDataType`

如：

- *SAMObject* 对象的 **Get()** 方法返回类型为 `SAMDataType` 。

## basBasis.h

调用库：**SAMModelDatabase.lib**

- static basBasis* **basBasis::Instance()**

    返回 SAM 进程中全局唯一控制 *Mdb*、*Ddb* 的 `basBasis` 单例父对象。

- const basMdb &**basBasis::Fetch()**

    返回 *basBasis* 控制的 *basMdb* 对象

    示例：

    ```cpp
    basBasis* bas = basBasis::Instance();

    //通过basBasis获取mdb对象
    basMdb mdb = bas->Fetch();
    ```

## basMdb.h

调用库：**SAMModelDatabase.lib**

- basModelMap **basMdb::GetModels()**

    返回*Mdb*下的模型`basNewModel`-名字映射表。

    示例：

    ```cpp
    basModelMap modelsMap = mdb.GetModels();
    ```

## basModelMap.h

调用库：**SAMModelDatabase.lib**

- cowListString **basModelMap::Keys()**

    返回*basModelMap*中`cowListString`类型的模型名字的列表。

    示例：

    ```cpp
    //通过basModelMap获取模型名称列表
    cowListString modelList = modelsMap.Keys();
    ```

## ptoKUtils.h

调用库：SAMGeometryComponent.lib

- const ptoKPartRepository& **ptoKConstGetPartRepos(const basMdb&, const QString &modelName)**

    返回存储有模型下 *Parts* 对象的`ptoKPartRepository`表。

    示例：

    ```cpp
    const ptoKPartRepository& parts = ptoKConstGetPartRepos(mdb, s);

    //利用返回的parts表获取Part名称
    for (int p = 1; p <= parts.Size(); ++p) {
	    QString partname = parts.GetKey(p);
    }
    ```

## ptoKPartRepository.h

调用库：SAMGeometryComponent.lib

- const QString& **ptoKPartRepository::GetKey(uint)**

    返回`ptoKPartRepository`中序号下的Part名称。

- const ptoKPart& **ptoKPartRepository::ConstGet(uint)**

    返回 *ptoKPartRepository* 中特定编号下 `ptoKPart` 类型的 *Part* 。

## ptoKPart.h

调用库：SAMPrimaryObjects.lib，SAMCoreAttributes.lib

- ftrFeatureList* **ptoKPart::GetFeatureList()** const

    该方法继承自`ftrPrimaryObject`，返回 *Part* 对象的 `FeatureList` 列表，包括其网格数据的引用等。

    示例：

    ```cpp
    ftrFeatureList* flpart = part.GetFeatureList();

    //利用FeatureList获取网格数据
    const bmeMesh* objectMesh = flpart->ConstGetMesh(bdoDefaultInstId);
    ```

## bmeMesh.h

调用库：SAMCoreMeshDefs.lib

- const bmeNodeData& **bmeMesh::NodeData()** const

    获取 *bmeMesh* 对象的 `Node` 节点数据。

- const bmeElementData& **bmeMesh::ElementData()** const

    获取 *bmeMesh* 对象的 `Element` 单元数据。

- uint
**bmeMesh::NumNodes()** const

    获取 *Mesh* 中节点的数量。

## bmeNodeData.h

调用库：SAMCoreMeshDefs.lib

- const utiCoordCont3D& **bmeNodeData::CoordContainer()** const

    获取 *NodeData* 中点的 `utiCoordCont3D` 类型的坐标数据容器。两者结合使用获取坐标见章节 <u>utiCoordCont3D.h</u> 的示例 

## bmeElementData.h

调用库：SAMCoreMeshDefs.lib

- const bmeElementClassList& **bmeElementData::ConstGetClasses()** const

    获取 *ElementData* 对象的 `bmeElementClassList` 单元对象列表。 

## bmeElementClassList.h

- const int **bmeElementClassList::Size()** const

    获取 *ElementClassList* 中的单元数量。

## utiCoordCont3D.h

- bool **utiCoordCont3D::GetCoord(int  index, float  &x, float  &y, float  &z)** const;


    示例：

    ```cpp
    //获取容器
    utiCoordCont3D nodeContainer = nodeData.CoordContainer();

    //使用utiCoordCont3D容器获取点的坐标，index为点的内部序号而非UserLabel
    nodeContainer.GetCoord(index, x, y, z);
    ```
