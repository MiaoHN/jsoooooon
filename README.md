# Jsoooooon

一个低效的 json 解析器

## json 数据结构

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

## 错误处理

## 示例代码

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

## 参考

- [Introducing JSON](https://www.json.org/)
