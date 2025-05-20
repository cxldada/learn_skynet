bag = {
}
bagmt = {
  put = function (b, item)
    table.insert(b.items, item)
  end,
  log = function (b)
    print(pair(b.items))
  end

}

bagmt["__index"] = bagmt
function bag.new()
  local t = {
    items = {}
  }
  setmetatable(t, bagmt)
  return t;
end

local b = bag.new()
b:put("apple")
b:log()

