#include "parser.h"

namespace Jsoooooon {

Json Parser::ParseFromFile(const std::string& path) {
  std::ifstream f;
  f.open(path);

  _data = std::string((std::istreambuf_iterator<char>(f)),
                      std::istreambuf_iterator<char>());
  return parse();
}

Json Parser::ParseFromString(const std::string& str) {
  _data = str;
  // TODO
  return parse();
}

Json Parser::parse() { return parse_object(); }

void Parser::skip_whitespace() {
  while (curr < _data.size() && (_data[curr] == ' ' || _data[curr] == '\n' ||
                                 _data[curr] == '\t' || _data[curr] == '\r')) {
    ++curr;
  }
}

std::string Parser::parse_string() {
  std::stringstream s;
  assert(_data[curr++] == '"');
  while (curr < _data.size()) {
    if (_data[curr] == '\\') {
      curr++;
      char c = _data[curr];
      if (c == 'n') {
        s << "\n";
        ++curr;
      } else if (c == '"') {
        s << '"';
        ++curr;
      } else if (c == 'r') {
        s << '\r';
        ++curr;
      }
    } else if (_data[curr] == '"') {
      curr++;
      return s.str();
    } else {
      s << _data[curr];
      curr++;
    }
  }
  return s.str();
}

double Parser::parse_number() {
  double result = 0.;
  int flag = 1;
  // 符号
  if (_data[curr] == '-') {
    flag = -1;
    ++curr;
  } else if (_data[curr] == '+') {
    ++curr;
  }
  if (_data[curr] == 0) {
    ++curr;
    if (_data[curr] == 'x') {
      // TODO 16 进制
    } else if (_data[curr] == 'b') {
      // TODO 2 进制
    } else if (_data[curr] == '0') {
      // TODO 8 进制
    }
  } else if (_data[curr] == '.') {
    // 直接到小数
    curr++;
    double aft = 0.;
    double b = 1.;
    while (isdigit(_data[curr])) {
      b /= 10.;
      double n = _data[curr++] - '0';
      aft += n * b;
    }
    result += aft;
  } else {
    // [1~9][0~9]*.[0~9][Ee][+-][1~9][0~9]*
    while (isdigit(_data[curr])) {
      double n = _data[curr] - '0';
      ++curr;
      result = n + result * 10.;
    }
    if (_data[curr] == '.') {
      curr++;
      double aft = 0.;
      double b = 1.;
      while (isdigit(_data[curr])) {
        b /= 10.;
        double n = _data[curr++] - '0';
        aft += n * b;
      }
      result += aft;
    }
  }
  if (_data[curr] == 'e' || _data[curr] == 'E') {
    curr++;
    int val = parse_number();
    bool f = val > 0;
    val = abs(val);
    double t = 1;
    for (int i = 0; i < val; ++i) {
      t *= 10;
    }
    if (f) {
      result *= t;
    } else {
      result /= t;
    }
  }

  return result * flag;
}

Json Parser::parse_object() {
  Json json;
  skip_whitespace();
  if (_data[curr] != '{') {
    std::cout << "warn near {" << std::endl;
    exit(-1);
  }
  ++curr;
  while (true) {
    skip_whitespace();
    if (_data[curr] != '"') {
      std::cout << "warn near \"" << std::endl;
      exit(-1);
    }
    std::string key = parse_string();
    skip_whitespace();
    if (_data[curr] != ':') {
      std::cout << "warn near :" << std::endl;
      exit(-1);
    }
    ++curr;
    skip_whitespace();
    Value value = parse_value();
    json.AddNode(key, value);
    if (_data[curr] != ',') {
      break;
    } else {
      ++curr;
    }
  }
  skip_whitespace();
  if (_data[curr] != '}') {
    std::cout << "warn near }" << std::endl;
    exit(-1);
  } else {
    curr++;
  }

  return json;
}

Value Parser::parse_list() {
  Value value;
  assert(_data[curr] == '[');
  ++curr;
  std::vector<Value> vec;
  while (curr < _data.size()) {
    Value val = parse_value();
    vec.push_back(val);
    if (_data[curr] != ',') {
      if (_data[curr] == ']') {
        curr++;
        break;
      } else {
        std::cout << "warn near ]" << std::endl;
        exit(-1);
      }
    } else {
      ++curr;
    }
  }
  value.SetList(vec);

  return value;
}

Value Parser::parse_value() {
  skip_whitespace();
  Value value;
  // type
  switch (_data[curr]) {
    // 字符串
    case '\"': {
      value.SetString(parse_string());
      break;
    }
    // 布尔类型
    case 't':
    case 'f': {
      value.SetBool(parse_bool());
      break;
    }
    // null 类型
    case 'n': {
      parse_null();
      value.SetNull();
      break;
    }
    // object
    case '{': {
      value.SetJson(std::make_shared<Json>(parse_object()));
      break;
    }
    // list
    case '[': {
      value = parse_list();
      break;
    }
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      value.SetNumber(parse_number());
      break;
    }
  }
  skip_whitespace();
  return value;
}

bool Parser::parse_bool() {
  if (_data[curr] == 'f') {
    assert(curr + 5 <= _data.size());
    assert(_data[curr++] == 'f');
    assert(_data[curr++] == 'a');
    assert(_data[curr++] == 'l');
    assert(_data[curr++] == 's');
    assert(_data[curr++] == 'e');
    return false;
  } else {
    assert(curr + 4 <= _data.size());
    assert(_data[curr++] == 't');
    assert(_data[curr++] == 'r');
    assert(_data[curr++] == 'u');
    assert(_data[curr++] == 'e');
    return true;
  }
}

void Parser::parse_null() {
  assert(curr + 4 <= _data.size());
  assert(_data[curr++] == 'n');
  assert(_data[curr++] == 'u');
  assert(_data[curr++] == 'l');
  assert(_data[curr++] == 'l');
}

}  // namespace Jsoooooon
