import os
import shutil

print("Material icons transfer started...")

for category in os.listdir("./material-icons"):
	category_dir = os.path.join("/home/yahya/Downloads/material-icons", category)
	for subcategory in os.listdir(category_dir):
		if os.path.isdir(os.path.join(category_dir, subcategory, "materialiconsoutlined")):
			icon_dir = os.path.join(category_dir, subcategory, "materialiconsoutlined", "48dp", "2x")
		elif os.path.isdir(os.path.join(category_dir, subcategory, "materialiconsround")):
			icon_dir = os.path.join(category_dir, subcategory, "materialiconsround", "48dp", "2x")
		elif os.path.isdir(os.path.join(category_dir, subcategory, "materialicons")):
			icon_dir = os.path.join(category_dir, subcategory, "materialicons", "48dp", "2x")
		elif os.path.isdir(os.path.join(category_dir, subcategory, "materialiconssharp")):
			icon_dir = os.path.join(category_dir, subcategory, "materialiconssharp", "48dp", "2x")
		else:
			icon_dir = os.path.join(category_dir, subcategory, "materialiconstwotone", "48dp", "2x")

		temp = os.listdir(icon_dir)
		icon_location = temp[0]
		icon = os.path.join(icon_dir, icon_location)
		raw_name_parts = icon_location.split('.').pop(0).split('_')
		raw_name_parts.pop(0)
		raw_name_parts.pop(-1)
		raw_name_parts.pop(-1)
		raw_name = '_'.join(raw_name_parts)
		raw_name = raw_name + ".png"
		dest = os.path.join("/home/yahya/Downloads/materialicons", raw_name)
		shutil.copyfile(icon, dest)