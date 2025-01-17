# 🕹️ The Club at the Center of the World
**A Futuristic Dystopian Game Set in Cape Town (Unreal Engine 5.5)**  

## 📖 Overview 
In **The Club at the Center of the World**, you play as a young man navigating a divided world where the ultra-rich control the city through an exclusive club called **The Agora**. Your mission is to infiltrate this hidden society and spark a revolution to take back control.  

The game is built using **Unreal Engine 5.5**, featuring **MetaHuman characters**, a dynamic **Gameplay Ability System (GAS)**, and customizable outfits using **MetaTailor**.

---

## 🛠️ Features  
- **Unreal Engine 5.5.1** is used exclusively as the game engine
- **MetaHuman characters** with custom clothing  
- **Gameplay Ability System (GAS)** for abilities and attributes  
- **Dynamic inventory system**  
- **Dystopian Cape Town environment**  
- **Root motion animations and Motion Matching** for realistic movement

---

## 📦 Setting up Visual Studio and Unreal Engine 5.5

- Download Unreal Engine 5.5.1 - It's important that you use this version
- Download Visual Studio Community Edition 2022
- Generate VS Project Files
- In Unreal Engine, set IDE to Visual Studio 2022 and Refresh Solution from Tools -> Refresh Visual Studio Solution (This is important to get intellisense working)
- Set the Default Project to Aura and the Launch Mode to DebugGame Editor

## 📦 How to Add Custom Clothing for MetaHumans  

This section explains how to add **custom clothing to MetaHumans** using **MetaTailor** and then import them into Unreal Engine.  

### ✅ **Step 1: Export the Head and Face FBX**  
1. In Unreal Engine, open your MetaHuman character.  
2. Export the **head and face FBX** to use as a reference in MetaTailor.  

### ✅ **Step 2: Convert to 2013 FBX Using Autodesk FBX Converter**  
1. Download and install the **Autodesk FBX Converter**.  
2. Use the tool to **convert the exported FBX** to **FBX 2013** format.  
   - This is required for compatibility with MetaTailor.  

### ✅ **Step 3: Download Clothes and Add to MetaTailor**  
1. Visit **MetaTailor** and upload the **converted head and face FBX**.  
2. Download or design your clothing assets and **add them to MetaTailor**.

### ✅ **Step 4: Export the Clothes from MetaTailor**  
1. In MetaTailor, export the clothing as an **FBX file with the full avatar** (free version).  
2. Make sure to choose the correct settings for Unreal Engine compatibility.

### ✅ **Step 5: Import into Blender and Adjust Orientation**  
1. Open the exported **FBX file** in **Blender**.  
2. **Remove the avatar mesh**, leaving only the clothing items.  
3. **Rotate the clothing** so that **X is the forward vector** (important for Unreal Engine).  
4. **Export each piece of clothing individually**, making sure the **root armature is selected**.

### ✅ **Step 6: Import into Unreal Engine**  
1. In Unreal Engine, import each clothing piece as a **Skeletal Mesh**.  
2. Set the **Target Skeleton** to the **MetaHuman skeleton** during import.

### ✅ **Step 7: Attach the Clothing to the MetaHuman in Unreal**  
1. Add the clothing item to your **MetaHuman Blueprint**.  
2. **Add a Skeletal Mesh component** in the Blueprint and **set the master pose component** to the **MetaHuman root skeleton**.  
3. In the **Construction Script**, use the **Set Master Pose Component** node to ensure the clothing follows the character's animations.

# 🎨 MetaHuman Custom Grooms Workflow (Blender to Unreal Engine)

This guide explains how to create custom hair grooms in **Blender** and import them into **Unreal Engine** for use with MetaHumans.

Video Guide: https://www.youtube.com/watch?v=l0PiYCDmjBk

## 🚀 Quick Tips for MetaHuman Clothing  
- Ensure your clothing meshes are **rigged** to the **MetaHuman skeleton**.  
- Always **convert to FBX 2013** format before uploading to MetaTailor.  
- Use **Blender** to clean up and adjust clothing items before importing into Unreal Engine.  

---

## ✅ **Step 1: Import the Face Mesh into Blender**
1. Open **Blender** and create a new project.
2. **Import the MetaHuman face mesh** by selecting **File -> Import -> FBX**.
   - Use the **noah_face.fbx** or the appropriate MetaHuman face mesh.
3. Once imported, press **`Tab`** to go into **Edit Mode**.

## ✅ **Step 2: Prepare the Face Mesh**
1. In **Edit Mode**, select all faces and press **Alt + J** to **convert any tris to quads**.
2. Use the **Circle Select Tool** (`C`) to select the area of the face where the hair will be painted.
   - Be precise about the selection, depending on your hairline or groom design.
3. After selecting the desired faces, press **`P`** and choose **Selection** to **split** the selected area into a new mesh.

## ✅ **Step 3: Unwrap the UVs**
1. With the new mesh selected, press **`Tab`** to go into **Edit Mode**.
2. Press **A** to select all vertices.
3. Press **`U`** to open the **UV Mapping** menu and select **Unwrap**.
4. Switch to **UV Editing Mode** to adjust the UV map if necessary.

## ✅ **Step 4: Add an Empty Hair Groom**
1. Go back to **Object Mode**.
2. Keep the **face mesh** selected, then press **Shift + A** -> **Curves** -> **Empty Hair** to add an empty hair groom.
3. Select the empty hair groom, go into **Sculpt Mode**, and start **painting the hair**.

## ✅ **Step 5: Interpolate the Hair Curves**
1. At the bottom of Blender’s interface (next to the timeline), click on **Assets**.
2. Drag and drop the **Interpolate Curves Node** onto the groom in the viewport to start shaping the hair.
3. Use **different sculpting tools** to adjust the hair volume, length, and flow as needed.

## ✅ **Step 6: Apply Modifiers**
1. Once you're happy with the groom, apply the **modifiers** from **top to bottom** in the **Modifier Stack**.
2. Make sure to finalize any grooming adjustments before applying the modifiers.

## ✅ **Step 7: Convert Hair Curves to Particle System**
1. Select the groom **curves object** in **Object Mode**.
2. Go to **Object** -> **Convert** -> **Convert to Particle System**.
   - This will prepare the groom for export.
3. Go to Particle tab at the bottom right and Didsable Show emitter under Render and Viewport, also set Steps to 7 under both.
4. Also make sure there are no vertex groups on the mesh because Unreal with assume it's a static mesh instead of a Grrom

## ✅ **Step 8: Export the Hair as an Alembic File**
1. With the **mesh (not the hair curves) selected**, go to **File -> Export -> Alembic (.abc)**.
2. Use the following settings for export:
   - **Scale:** `100x`
   - **Selected and Visible Objects:** Enabled
   - **Frame Start/End:** `1`
   - **Settings:** Viewport
   - **Geometry:** Deselect all options under this category.

## ✅ **Step 9: Import the Hair into Unreal Engine**
1. Open **Unreal Engine** and go to your **MetaHuman project**.
2. Make sure you have the Alembic Groom Importer Addon installed in Unreal. 
3. Import the **Alembic file** by selecting **File -> Import Into Level**.
4. Create a Groom Binding and Attach to Face Mesh -> In this case the custom metahuman face mesh we created
4. Attach the groom to your **MetaHuman Blueprint** and adjust its settings to fit your character.
5. Also Add the binding to the groom asset

## 🛠 **Troubleshooting Tips**
- **Hair Appears Offset or Misaligned:**  
  Ensure that **normals are correctly recalculated** in Blender before exporting.

- **Hair Bugging out in Blender:**  
  Create a new Project and import the Face Mesh and start from scratch. Sometimes Hair Curves collide for some reason.
  
- **Hair Not Showing in Unreal Engine:**  
  Double-check your **Alembic import settings** and ensure you are using **Groom components** in Unreal.

---

## 📦 Resources
### Metahuman Customisation
- https://www.youtube.com/watch?v=b_ZjsUg2XCc - Metahuman customisation - Everything you need to know about Unreal to Blender and vice versa
