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

local len = #input
for i = 1, len, 16 do
	file:write("\n\t\"")
	for j = 0, 15 do
		file:write(string.format("\\x%02x", string.byte(input, i+j)))
	end
	file:write("\"")
end

if len % 16 ~= 0 then
	file:write("\n\t\"")
	local r = len % 16
	local i = len - r
	for j = 1, r - 1 do
		file:write(string.format("\\x%02x", string.byte(input, i+j)))
	end
	file:write("\"")
end

file:write(";\n")
file:close()
