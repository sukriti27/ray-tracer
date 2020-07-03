### Ray Tracer
<p align="justify">
Ray tracer based on 'Ray Tracing in One Weekend' book series and 'Scratchapixel 2.0'.
</p>

<b>Features</b>
1. <p align="justify">A basic pinhole camera has been implemented. The ﬁeld of view, look from vector, look at vector and view up vector of the camera can be speciﬁed in the model. The width and height of the output image are also speciﬁed in the model. The images below were obtained by changing the field of view of the camera from 130 to 110. </p>

<div align="center">
<img src="https://github.com/sukriti27/ray-tracer/blob/master/examples/finalImage.png" width="300" height="300" /> &nbsp; &nbsp; <img src="https://github.com/sukriti27/ray-tracer/blob/master/examples/110fov.png" width="300" height="300" />
</div>

2. <p align="justify">Point light source has been implemented. The intensity and direction of the light source needs to be speciﬁed in the model.</p>

3. <p align="justify">The ray tracer can be used to render spheres, planar quads, triangles and triangle meshes.</p>

4. <p align="justify">The ray tracer supports three types of materials: Blinn-Phong, reﬂective and transparent. Every shape is associated with a material. Primary rays from the camera intersect the shapes in the scene and the shading at the point of intersection is found based on the type of the material.</p>

5. <p align="justify">Texture can be added to the shapes by specifying the image texture location in the model.</p>

6. <p align="justify">The ray tracer can be used to simulate a thin lens camera to get the depth of ﬁeld effect as shown below. The thin lens camera takes two additional parameters compared to the pinhole camera - aperture and focal distance. On increasing the size of the aperture, the blur increases. The first image below has an aperture of 0.025 and the second image has an aperture of 0.05.</p>

<div align="center">
<img src="https://github.com/sukriti27/ray-tracer/blob/master/examples/smallaperture.png" width="308" height="230" /> &nbsp; &nbsp; <img src="https://github.com/sukriti27/ray-tracer/blob/master/examples/bigaperture.png" width="300" height="230" />
</div>

7. <p align="justify">Bounding Volume Hierarchy has been used for ray intersection acceleration. The ray tracer ﬁnds the bounding volume of each of the shapes in the scene. In addition, it ﬁnds the bounding volume that bounds each of these bounding volumes. If the ray misses this bounding volume, it will not hit any of the shapes. If it hits the bounding volume, it might hit one of the shapes. Axis-aligned bounding boxes or AABBs have been used.  A scene consisting of 21 spheres was considered to evaluate the efﬁciency of the BVH. The time taken to render through BVH was 28.75 seconds. The same scene took 51.07 seconds without BVH.</p>
