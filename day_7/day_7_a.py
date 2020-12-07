from collections import defaultdict
import re

input_file = 'input_7.txt'

bag_dict = dict()
contain_set = set()
with open(input_file, 'r') as f:
    for l in f:
        root_bag, other_bags = l.strip().split(" bags contain")
        root_bag = tuple(root_bag.split(" "))
        other_bags = re.split(" bags| bag", other_bags)[:-1]
        r = re.compile("[a-z]+ [a-z]+")
        bag_dict[root_bag] = set()
        for bag_descr in other_bags:
            bag = tuple(r.findall(bag_descr)[0].split(" "))
            if bag[0] != "no":
                bag_dict[root_bag].add(bag)

changed = True
while changed:
    changed = False
    for bag, contains in bag_dict.items():
        if ("shiny", "gold") in contains and bag not in contain_set:
            contain_set.add(bag)
            changed = True
            continue
        
        for contained_bag in contains:
            if contained_bag in contain_set and bag not in contain_set:
                contain_set.add(bag)
                changed = True

print(len(contain_set))
    