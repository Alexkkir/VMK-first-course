class CustomMeta():
    def __new__(cls, cls_name, super_classes, attr_dict):
        for attr_name, attr_value in attr_dict.items():
            if not attr_name.startswith('__'):
                attr_name_new = 'custom_' + attr_name
                attr_dict.pop(attr_name)
                attr_dict[attr_name_new] = attr_value
        return type(cls_name, super_classes, attr_dict)

class CustomClass(metaclass=CustomMeta):
    x = 50

    def line(self):
        return 100

# a = CustomClass()
# print(a.__getattribute__('custom_x'))
