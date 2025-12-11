# generated from rosidl_generator_py/resource/_idl.py.em
# with input from mpc_car_control:msg/ControlCommandBody.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ControlCommandBody(type):
    """Metaclass of message 'ControlCommandBody'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('mpc_car_control')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'mpc_car_control.msg.ControlCommandBody')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__control_command_body
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__control_command_body
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__control_command_body
            cls._TYPE_SUPPORT = module.type_support_msg__msg__control_command_body
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__control_command_body

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ControlCommandBody(metaclass=Metaclass_ControlCommandBody):
    """Message class 'ControlCommandBody'."""

    __slots__ = [
        '_header',
        '_fx',
        '_fy',
        '_mz',
        '_fz',
        '_mx',
        '_my',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'fx': 'double',
        'fy': 'double',
        'mz': 'double',
        'fz': 'double',
        'mx': 'double',
        'my': 'double',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.fx = kwargs.get('fx', float())
        self.fy = kwargs.get('fy', float())
        self.mz = kwargs.get('mz', float())
        self.fz = kwargs.get('fz', float())
        self.mx = kwargs.get('mx', float())
        self.my = kwargs.get('my', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.fx != other.fx:
            return False
        if self.fy != other.fy:
            return False
        if self.mz != other.mz:
            return False
        if self.fz != other.fz:
            return False
        if self.mx != other.mx:
            return False
        if self.my != other.my:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if self._check_fields:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def fx(self):
        """Message field 'fx'."""
        return self._fx

    @fx.setter
    def fx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'fx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fx = value

    @builtins.property
    def fy(self):
        """Message field 'fy'."""
        return self._fy

    @fy.setter
    def fy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'fy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fy = value

    @builtins.property
    def mz(self):
        """Message field 'mz'."""
        return self._mz

    @mz.setter
    def mz(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'mz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mz = value

    @builtins.property
    def fz(self):
        """Message field 'fz'."""
        return self._fz

    @fz.setter
    def fz(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'fz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'fz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._fz = value

    @builtins.property
    def mx(self):
        """Message field 'mx'."""
        return self._mx

    @mx.setter
    def mx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'mx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'mx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._mx = value

    @builtins.property
    def my(self):
        """Message field 'my'."""
        return self._my

    @my.setter
    def my(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'my' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'my' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._my = value
