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

std::string Parser::parse_key() {
  skip_whitespace();
  std::string key = parse_string();
  skip_whitespace();
  return key;
}

double Parser::parse_number() {
  double result = 0;
  int flag = 1;
  // 符号
  if (_data[curr] == '-') {
    flag = -1;
    ++curr;
  } else if (_data[curr] == '+') {
    ++curr;
  }

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
      double n = _data[curr] - '0';
      curr++;
      aft += n * b;
    }
    result += aft;
  }
  if (_data[curr] == 'e' || _data[curr] == 'E') {
    curr++;
    int flge = 1;
    if (_data[curr] == '-') {
      flge = -1;
      curr++;
    } else if (_data[curr] == '+') {
      curr++;
    }
    int val = 0;
    while (isdigit(_data[curr])) {
      double n = _data[curr] - '0';
      ++curr;
      val = n + val * 10.;
    }
    val *= flge;
    val = abs(val);
    double t = 1;
    for (int i = 0; i < val; ++i) {
      t *= 10;
    }
    if (flge > 0) {
      result *= t;
    } else {
      result /= t;
    }
  }

  return result * flag;
}

Json Parser::parse_object() {
  // object 内为 key: value 形式的键值对
  // { key1: value1, key2: value2, ... }
  skip_whitespace();
  Json json;
  assert(_data[curr++] == '{');
  while (true) {
    std::string key = parse_key();
    assert(_data[curr++] == ':');
    Value value = parse_value();
    json.AddNode(key, value);
    if (_data[curr] != ',') {
      break;
    }
    ++curr;
  }
  skip_whitespace();
  assert(_data[curr++] == '}');

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
  switch (_data[curr]) {
    case '"': {
      value.SetString(parse_string());
      break;
    }
    case 't':
    case 'f': {
      value.SetBool(parse_bool());
      break;
    }
    case 'n': {
      parse_null();
      value.SetNull();
      break;
    }
    case '{': {
      value.SetJson(std::make_shared<Json>(parse_object()));
      break;
    }
    case '[': {
      value = parse_list();
      break;
    }
    case '-':
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
