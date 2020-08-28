local args = {...}
if #args < 4 then
	error("usage: lua5.3 tocstr.lua <header> <cname> <in.lua> <out.c>")
end

local header, cname, path_in, path_out = table.unpack(args)

local file = io.open(path_in, "r")
local input = file:read("a")
file:close()

local file = io.open(path_in, "r")
if not file then
	error("failed to open " .. path_in)
end
local input = file:read("a")
file:close()

local file = io.open(path_out, "w")
if not file then
	error("failed to open " .. path_out)
end

file:write("#include ")
file:write(header)
file:write("\n\nconst char *")
file:write(cname)
file:write(" =")

local function splitToHex16(s)
	local t = {}
	for i = 1, #s, 16 do
		t[#t + 1] = string.gsub(s:sub(i, i + 15), ".", function(c)
			return string.format("\\x%02x", string.byte(c))
		end)
	end
	return t
end

if #input == 0 then
	file:write("\"\"")
else
	for i, line in ipairs(splitToHex16(input)) do
		file:write("\n\t\"")
		file:write(line)
		file:write("\"")
	end
end

file:write(";\n")
file:close()
