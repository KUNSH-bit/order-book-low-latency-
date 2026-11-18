#include <cstdint>
#include <iostream>
#include <stdexcept>

using namespace std;

enum class Side : uint8_t { Buy, Sell };

enum class Type : uint8_t { Limit, Market };

struct Order {
  uint64_t orderId;
  int64_t price;
  uint64_t quantity;
  Side side;

  uint32_t symbol;
  uint64_t partial;
  uint64_t time;
  Type type;

  Order(uint64_t id, int64_t p, uint64_t qty, Side s, uint32_t symbol,
        uint64_t t, Type type = Type::Limit)
      : orderId(id), price(p), quantity(qty), side(s), symbol(symbol),
        partial(0), time(t), type(type) {
    if (id == 0) {
      throw invalid_argument("Invalid Order ID: Must be non-zero.");
    }
    if (quantity == 0) {
      throw invalid_argument("Invalid Quantity: Must be greater than zero.");
    }
    if (type == Type::Limit && price <= 0) {
      throw invalid_argument(
          "Invalid Price: Limit order price must be positive.");
    }
  }

  bool apply_fill(uint64_t fill_qty) {
    if (fill_qty == 0) {
      return false;
    }

    if (partial + fill_qty > quantity) {
      return false;
    }

    partial += fill_qty;
    return true;
  }

  [[nodiscard]] uint64_t remaining_quantity() const {
    return quantity - partial;
  }

  [[nodiscard]] bool is_filled() const { return partial >= quantity; }
};

int main() {}