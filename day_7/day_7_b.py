from collections import defaultdict
import re


input_file = 'input_7.txt'


def get_bag_count(bag_dict, bag):
    if len(bag_dict[bag]) == 0:
        return 0
    
    sum = 0
    for contained_bag in bag_dict[bag]:
        sum += contained_bag[1] * (get_bag_count(bag_dict, contained_bag[0]) + 1)

    return sum


bag_dict = dict()
with open(input_file, 'r') as f:
    for l in f:
        root_bag, other_bags = l.strip().split(" bags contain")
        root_bag = tuple(root_bag.split(" "))
        other_bags = re.split(" bags| bag", other_bags)[:-1]
        r = re.compile("[a-z]+ [a-z]+")
        r_number = re.compile("[0-9]+")
        bag_dict[root_bag] = list()
        for bag_descr in other_bags:
            bag = tuple(r.findall(bag_descr)[0].split(" "))
            if bag[0] != "no":
                bag_count = int(r_number.findall(bag_descr)[0])
                bag_dict[root_bag].append((bag, bag_count))

print(get_bag_count(bag_dict, ("shiny", "gold")))