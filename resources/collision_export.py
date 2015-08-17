import struct
import bpy

"""FORMAT:
(number of names)
Null terminated strings

then

Polygon:
    poly type (I)
    plane normal (fff)
    num verts (I)
    some verticies [fff]
    edge links (I)
    
    
"""


obj = bpy.context.active_object

matNames = []
for mat in obj.data.materials:
    matNames.append(mat.name)
   
matNamesBytes = [struct.pack('I',len(matNames))]
for n in matNames: matNamesBytes.append(
    struct.pack('I',len(n)) + bytes(n,'utf-8')
    )



#polygons

class Polygon(object):
    Trifloat = struct.Struct('fff')
    Int = struct.Struct('I')
    
    def __init__(self,i,type,normal):
        self.i = i
        self.type = type
        self.verts = []
        self.normal = normal
        self.links = []
        self.verts = []
        
        self.indexToEdgeTuple = {}
        self.linksIndexedByEdgeTuple = {}
    
    def pack(self):
        b = []
        b.append( self.Int.pack(self.type) ) #polygon type
        b.append( self.Trifloat.pack(self.normal[0],self.normal[1],self.normal[2]) ) #face normal
        b.append( self.Int.pack(len(self.verts)) ) #num verts
        
        for v in self.verts:
            b.append( self.Trifloat.pack(v[0],v[1],v[2]) ) #verts
        for l in self.links:
            if l:
                b.append( self.Int.pack(l.i) ) #links
            else:
                b.append( self.Int.pack(4294967295) ) #unconnected links are assigned to the max int
        
        return bytes().join(b)




polygonsByEdge = {}
polygons = []

n = 0
for f in obj.data.polygons:
    p = Polygon(n,f.material_index,f.normal)
    polygons.append(p)
    n += 1
    
    for idx in f.vertices:
        p.verts.append(obj.data.vertices[idx].co)
    
    
    
    i = 0;
    for edgeKey in f.edge_keys:
        p.indexToEdgeTuple[i] = edgeKey
        i += 1
        
        try:
            p2 = polygonsByEdge[edgeKey]
            p2.linksIndexedByEdgeTuple[edgeKey] = p
            p.linksIndexedByEdgeTuple[edgeKey] = p2
            
        except KeyError:
            polygonsByEdge[edgeKey] = p


for p in polygons:
    for i in range(len(p.indexToEdgeTuple.keys())):
        edgeTuple = p.indexToEdgeTuple[i]
        
        if edgeTuple in p.linksIndexedByEdgeTuple:
            p.links.append(p.linksIndexedByEdgeTuple[edgeTuple])
        else:
            p.links.append(None)
        



polygonBytes = [struct.pack('I',len(polygons))]
num = 0
numPartlinked = 0
for p in polygons:
    num += 1
    if (not p.links[0]) or (not p.links[1]) or (not p.links[2]):
        numPartlinked += 1
    polygonBytes.append(p.pack())

print (num,numPartlinked )

b = bytes()
b = b.join(matNamesBytes + polygonBytes)
f = open("J:/Program Files/CodeLite/3D1/3D1/resources/collision.bin",'wb')
f.write(b)
f.close()