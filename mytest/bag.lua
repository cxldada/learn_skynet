CBag = {}
CBagMT = {
  put = function(b, item)
    table.insert(b.items, item)
  end,
  log = function(b)
    for k, v in pairs(b.items) do
      print(k, v)
    end
  end,
}
CBagMT["__index"] = CBagMT

function CBag.new()
  local bag = {
    items = {},
  }
  setmetatable(bag, CBagMT)
  return bag
end

local bag = CBag.new()
bag:put("apple")
bag:log()
