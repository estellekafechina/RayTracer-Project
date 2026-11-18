# Discovery report

## Problem statement

A renowned Los Angeles film studio needs a trustworthy, maintainable and extensible ray tracer that can render complete animated films fast enough, because its current Maya-based solution is too expensive and does not meet all of its needs.

## Client interview summary

### Production and current tools

**Need:** A more affordable tool suited to the studio's animation work.

> **Q (Maktar):** "What kind of animation do they produce?"
>
> **A:** "Complex animations."

> **Q (Maktar):** "What solution are they currently using?"
>
> **A:** "Autodesk Maya."

> **Q (Gautier):** "Why do they want to stop using Maya?"
>
> **A:** "Maya is too expensive and does not meet all their requirements."

**My conclusion:** Cost and unmet needs motivate the project. The missing features are unknown.

### Hardware and rendering

**Need:** Fast rendering with acceptable image quality on existing hardware.

> **Q (William):** "What is a reasonable render time for you?"
>
> **A:** "Very fast."

> **Q (A Colleague):** "What kind of hardware do you have?"
>
> **A:** "CPU-only hardware with Intel processors."

**My conclusion:** Speed is important, but no render-time target was given. CPU support is required.

### Delivery and maintenance

**Need:** A production-ready tool that the studio can maintain.

> **Q (Djedje):** "What is the production deadline?"
>
> **A:** "The ray tracer must be ready for production use by January 15 2027."

> **Q (Maktar):** "Who will be responsible for maintenance?"
>
> **A:** "Maintenance will be handled in-house, with support from selected external partners when needed."

**My conclusion:** Maintenance must be manageable internally.

### Image quality and diagnostics

**Need:** Artefact-free images and clear error explanations.

> **Q (Dhiki):** "What would demonstrate that the new ray tracer meets your needs?"
>
> **A:** "It should produce images without visual artefacts. If a problem occurs, users should be able to identify its exact cause."

**My conclusion:** Image quality and diagnostics are key acceptance criteria.

### Open questions

- What problem led you to request a new ray tracer? (Beyond cost and unmet Maya requirements.)
- Could you show us examples of the images you expect the ray tracer to produce?
- What kinds of 3D scenes do you typically work with?
- What maximum render time per frame would count as “very fast”?
- Who will use the ray tracer in your studio, and for which tasks?
- Could you walk us through how you currently render a scene?
- Where do your renders currently run: on individual workstations or a render farm?
- Which 3D software and file formats do you currently use? (Maya is known; formats are not.)
- Can you describe a recent situation where your current rendering tools did not meet your needs?
- What technical constraints do you currently face when rendering?
- How do you expect the ray tracer to fit into your existing production process?

## State of the art

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| Maya with Arnold | Autodesk | Proprietary subscription | Maya: USD 255/month or USD 2,010/year; batch-rendering licences may cost extra (checked November 16, 2026) | CPU or NVIDIA GPU Monte Carlo ray tracing; physically based materials, global illumination, volumes, hair, motion blur, AOVs and direct Maya integration. | [Maya price](https://www.autodesk.com/products/maya/overview/), [Arnold for Maya](https://help.autodesk.com/cloudhelp/2027/ENU/Maya-Rendering/files/GUID-AD1E74F3-471A-4B5D-8FB0-9E4EC6EC5252.htm), [render settings](https://help.autodesk.com/cloudhelp/2027/ENU/AR-Maya/files/am-Arnold_for_Maya_User_Guide/arnold_for_maya_render_settings_html.html) |
| RenderMan 27 | Pixar | Proprietary commercial licence; free non-commercial edition | USD 595 per licence plus USD 250 annual maintenance (checked November 16, 2026) | CPU rendering and hybrid CPU/GPU rendering; path tracing, production materials, hair, volumes, denoising, checkpointing, AOVs and integrations with Maya and other DCC tools. | [RenderMan pricing](https://prod.renderman.pixar.com/store), [technical specifications](https://prod.renderman.pixar.com/tech-specs) |
| Blender with Cycles | Blender Foundation | Blender: GNU GPL; Cycles: Apache 2.0 | Free and open source (checked November 16, 2026) | CPU or GPU path tracing; physically based materials, global illumination, volumes, hair, motion blur, denoising, render passes and integration with Blender's animation toolset. | [Blender licence](https://www.blender.org/about/license/), [Cycles settings](https://docs.blender.org/manual/en/5.0/render/cycles/render_settings/index.html) |
| MoonRay | Academy Software Foundation; originally DreamWorks Animation | Apache 2.0 | Free and open source (checked November 16, 2026) | Vectorized CPU production path tracing, distributed rendering and optional hybrid GPU acceleration; production materials, hair, volumes, checkpointing, AOVs, profiling and USD/Hydra integration. | [MoonRay repository and licence](https://github.com/OpenMoonRay/openmoonray), [features](https://openmoonray.org/about), [execution modes](https://docs.openmoonray.org/user-reference/execution-modes/) |

**Conclusion:** All four solutions provide physically based rendering, CPU support and features used in animation production. Arnold and RenderMan offer mature integrations and commercial support, but their licence costs conflict with the client's concern about Maya. Blender/Cycles and MoonRay remove licence fees and expose their source code, but the studio would take responsibility for integration, training and maintenance. MoonRay is particularly relevant because it was designed for feature animation, distributed CPU rendering, diagnostics and external contributions. No final choice can be made until the studio explains which Maya capabilities are missing and provides representative scenes, target render times and its exact Intel hardware.

## What is ray tracing?

Ray tracing takes a description of a 3D scene as input, including its camera, objects, materials and lights, and produces a 2D image or a sequence of animation frames. For each pixel, the renderer sends a mathematical ray from the camera into the scene, finds the nearest object it hits and calculates the colour from the material and incoming light. It sends more rays to detect shadows and simulate reflections, refractions and indirect light. An acceleration structure can avoid testing every object in a complex scene. More samples and light bounces usually reduce noise and improve realism, but also increase render time.

**Sources:** Start with [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). Reference: [Physically Based Rendering](https://pbr-book.org/4ed/contents).

## What is C++?

C++ is a compiled, statically typed language that offers high-level abstractions as well as direct control over memory and hardware. This makes it suitable for a CPU ray tracer, where mathematical operations, memory layout and predictable performance matter.

### Programming paradigms

C++ supports procedural, object-oriented, generic and functional programming. Like the higher-level languages I already know, it uses functions and objects to organize behaviour, but it gives me more choice over how data is represented and processed. A renderer can use procedural or data-oriented code for intensive loops, composition and objects for concepts such as cameras and materials, templates for reusable vector code, and small pure functions for calculations that are easy to test.

### What to watch out for

Compared with managed languages, C++ leaves more responsibility to the developer. Object lifetime and ownership must be clear because invalid pointers can crash the program and manual allocation can leak memory; RAII, standard containers and smart pointers reduce these risks. Floating-point rounding can create visible artefacts, and parallel code can create data races. Compiler warnings, sanitizers, deterministic tests and profiling are therefore important.

### Shaping the domain model

The model should start with simple concepts such as `Scene`, `Camera`, `Ray`, `Geometry`, `Material`, `Light`, `Renderer`, `Colour` and `Image`. `Scene` owns the camera, objects, materials and lights, while `Renderer` coordinates the work and `Image` stores the result. A `Sphere` and an `Image` hold colours, and for now the `trace` function decides the colour of one pixel from a ray and a sphere. Composition is clearer than a deep inheritance tree for most relationships. Polymorphism is useful when several shapes or materials share an interface, but ownership and performance should remain visible. Keeping these responsibilities separate will make the code easier to test, maintain and extend.

**Sources:** Start with [LearnCpp](https://www.learncpp.com/). Reference: [cppreference](https://en.cppreference.com/w/) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).
