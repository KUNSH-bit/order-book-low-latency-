#include <cstdint>
#include <iostream>

using namespace std;

enum class Side : uint8_t { Buy, Sell };

enum class Type : uint8_t { Limit, Market };

struct Order {
  uint64_t orderId;
  uint64_t price;
  uint64_t quantity;
  Side side;

  uint32_t symbol;
  uint64_t partial;
  uint64_t time;
  Type type;

  Order(uint32_t id, uint64_t p, uint64_t qty, Side s, uint32_t symbol,
        uint64_t t, Type type = Type::Limit)
      : orderId(id), price(p), quantity(qty), side(s), symbol(symbol),
        partial(0), time(t), type(type) {}

  [[nodiscard]] uint64_t remaining_quantity() const {
    return quantity - partial;
  }

  [[nodiscard]] bool is_filled() const { return partial >= quantity; }
};

int main() {}