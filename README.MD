# 🕹️ The Club at the Center of the World
**A Futuristic Dystopian Game Set in Cape Town (Unreal Engine 5.5)**  

## 📖 Overview  
In **The Club at the Center of the World**, you play as a young man navigating a divided world where the ultra-rich control the city through an exclusive club called **The Agora**. Your mission is to infiltrate this hidden society and spark a revolution to take back control.  

The game is built using **Unreal Engine 5.5**, featuring **MetaHuman characters**, a dynamic **Gameplay Ability System (GAS)**, and customizable outfits using **MetaTailor**.

---

## 🛠️ Features  
- **MetaHuman characters** with custom clothing  
- **Gameplay Ability System (GAS)** for abilities and attributes  
- **Dynamic inventory system**  
- **Dystopian Cape Town environment**  
- **Root motion animations** for realistic movement  

---

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

---

## 🚀 Quick Tips for MetaHuman Clothing  
- Ensure your clothing meshes are **rigged** to the **MetaHuman skeleton**.  
- Always **convert to FBX 2013** format before uploading to MetaTailor.  
- Use **Blender** to clean up and adjust clothing items before importing into Unreal Engine.  

---

## 📦 Incredicle Resources
- https://www.youtube.com/watch?v=b_ZjsUg2XCc - Metahuman customisation - Everything you need to know about Unreal to Blender and vice versa