struct Board {
  struct Memory {
    Memory(uint8_t* data, uint size) : data(data), size(size) {}
    Memory() : data(nullptr), size(0u), writable(false) {}
    ~Memory() { if(data) delete[] data; }

    inline auto read(uint addr) const -> uint8;
    inline auto write(uint addr, uint8 data) -> void;

    string name;
    uint8_t* data = nullptr;
    uint size = 0;
    bool writable = false;
  };

  virtual ~Board() = default;

  static auto mirror(uint addr, uint size) -> uint;

  Board(Markup::Node document = {});
  virtual auto load() -> void;
  virtual auto save() -> void;

  virtual auto main() -> void;
  virtual auto tick() -> void;

  virtual auto readPRG(uint addr) -> uint8 { return 0x00; }
  virtual auto writePRG(uint addr, uint8 data) -> void {}

  virtual auto readCHR(uint addr) -> uint8;
  virtual auto writeCHR(uint addr, uint8 data) -> void;

  virtual inline auto scanline(uint y) -> void {}

  virtual auto power() -> void;

  virtual auto serialize(serializer&) -> void;

  static auto load(string manifest) -> Board*;

  struct Information {
    string type;
  } information;

  Memory prgrom;
  Memory prgram;
  Memory chrrom;
  Memory chrram;
};
