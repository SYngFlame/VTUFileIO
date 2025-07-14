# 二次开发接口使用说明
## basBasis.h

调用库：**SAMModelDatabase.lib**

- basBasis* **basBasis::Instance()**

    返回SAM进程中控制**Mdb**、**Ddb**的`basBasis`父对象。

    示例：

    ```cpp
    basBasis* bas = basBasis::Instance();

    //通过basBasis获取mdb对象
    basMdb mdb = bas->Fetch();
    ```

## basMdb.h

调用库：**SAMModelDatabase.lib**

- basModelMap **basMdb::GetModels()**

    返回**Mdb**下的模型`basNewModel`-名字映射表。

    示例：

    ```cpp
    basModelMap modelsMap = mdb.GetModels();
    ```

## basModelMap.h

调用库：**SAMModelDatabase.lib**

- cowListString **basModelMap::Keys()**

    返回**basModelMap**中`cowListString`类型的模型名字的列表。

    示例：

    ```cpp
    //通过basModelMap获取模型名称列表
    cowListString modelList = modelsMap.Keys();
    ```

## ptoKUtils.h

调用库：SAMGeometryComponent.lib

- const ptoKPartRepository& **ptoKConstGetPartRepos(const basMdb&, const QString &modelName)**

    返回存储模型下的Parts的`ptoKPartRepository`表。

    示例：

    ```cpp
    const ptoKPartRepository& parts = ptoKConstGetPartRepos(mdb, s);

    //利用返回的parts表获取Part名称
    for (int p = 1; p <= parts.Size(); ++p) {
	    QString partname = parts.GetKey(p);
    }
    ```

- const QString& **ptoKPartRepository::GetKey(uint)**

    返回`ptoKPartRepository`中序号下的Part名称。

- const ptoKPart& **ptoKPartRepository::ConstGet(uint)**

    返回`ptoKPartRepository`中序号下ptoKPart类型的Part。


- ftrFeatureList* **ptoKPart::GetFeatureList()**

    该方法继承自`ftrPrimaryObject`，返回Part对象的FeatureList列表，包括其网格数据的引用等。

    示例：

    ```cpp
    ftrFeatureList* flpart = part.GetFeatureList();

    //利用FeatureList获取网格数据
    const bmeMesh* objectMesh = flpart->ConstGetMesh(bdoDefaultInstId);
    ```