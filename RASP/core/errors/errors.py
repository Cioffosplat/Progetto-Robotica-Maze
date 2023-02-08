class EncoderOverflowError(Exception):
    """Data overflow"""
    pass


class MissingDelimitersError(Exception):
    """Missing START or STOP tokens"""
    pass


class NoCellsMatch(Exception):
    pass


class StopExecution(Exception):
    pass


class HandshakeException(Exception):
    def __init__(self, v):
        self.value = v