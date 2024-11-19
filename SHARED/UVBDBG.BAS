'-----------------------------------------------------------------------
' uvbdbg.bas
'-----------------------------------------------------------------------
' Copyright (c) 1993-1994 Microsoft Corporation
'                   All Rights Reserved
' Information Contained Herein Is Proprietary and Confidential
'-----------------------------------------------------------------------
'
'
' Owner: daviddow
'
' History:
'   6/8/93      created.
'-----------------------------------------------------------------------

Sub Assert (strFn As String)
    Dim ret As Integer

    ret = MsgBox("ASSERT: " & strFn, MB_ABORTRETRYIGNORE + MB_ICONEXCLAMATION + MB_SYSTEMMODAL, "Assert")
    If ret = IDABORT Then End
End Sub

Function AssertError (errV As Integer, errl As Long, strFn As String) As Integer
    Dim ret As Integer

    ret = MsgBox("Error: " & Error$(errV) & errV & " at: " & strFn & " line: " & errl, MB_ABORTRETRYIGNORE + MB_ICONEXCLAMATION+ MB_SYSTEMMODAL, "Error")
    If ret = IDABORT Then End
    AssertError = ret
End Function

Sub NotImplemented (strFn As String)
    Dim ret As Integer

    ret = MsgBox("Not Implemented: " & strFn, MB_ICONEXCLAMATION + MB_SYSTEMMODAL, "NYI")
End Sub

