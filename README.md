# Jsoooooon

一个~~低效的~~ json 解析器

## json 文件结构

```
json       -> { Whitespace objects Whitespace }
objects    -> objects Whitespace , Whitespace object | object
object     -> key Whitespace : Whitespace value
key        -> string
value      -> list | json | number | string | true | false | null
string     -> "..."
number     ->
list       -> [ Whitespace item Whitespace ]
item       -> item Whitespace , Whitespace value | value
Whitespace -> Whitespace whitespace | whitespace
whitespace -> ' ' | '\t' | '\n'
```

## 示例代码

测试的 json 文件：

```json
{
  "personData": [
    {
      "age": 12,
      "name": "nate",
      "schoolInfo": [
        {
          "School_name": "清华"
        },
        {
          "School_name": "北大"
        }
      ],
      "url": "http://pic.yesky.com/uploadImages/2014/345/36/E8C039MU0180.jpg"
    },
    {
      "age": 24,
      "name": "jack"
    }
  ],
  "result": 1
}
```

代码：

```cpp
#include <iostream>

#include "json.h"

int main(int argc, char** argv) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json   json = parser.ParseFromFile(filepath);

  std::cout << "result: " << json["result"].ToString() << std::endl;
  return 0;
}
```

输出：

```bash
result: 1.000000
```

## TODO

- [ ] 完善对数字的判断
- [ ] string 中对特殊编码的支持
- [ ] json 输出格式化
- [ ] 通过类似于 map 的操作方式对 json 进行处理

## 参考

- [Introducing JSON](https://www.json.org/)
