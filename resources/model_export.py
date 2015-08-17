import struct
import bpy

objs = bpy.context.selected_objects

v = []
c = []
n = []
for obj in objs:
    for f in obj.data.polygons:
        color = obj.data.materials[f.material_index].diffuse_color
        normal = f.normal
        for idx in f.vertices:
            v.append(obj.data.vertices[idx].co)
            c.append(color)
            n.append(normal)




st = struct.Struct('fff')

bv = []
for a in v: bv.append(st.pack(a[0],a[1],a[2]))
bc = []
for a in c: bc.append(st.pack(a[0],a[1],a[2]))
bn = []
for a in n: bn.append(st.pack(a[0],a[1],a[2]))


b = bytes()
b = b.join(bv+bc+bn)
f = open("J:/Program Files/CodeLite/3D1/3D1/resources/model.bin",'wb')
f.write(b)
f.close()
print("Done! "+str(len(b))+' '+str(len(v)))