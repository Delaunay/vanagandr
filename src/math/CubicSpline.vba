Option Base 1
 
Function cubic_spline(x As Range, fx As Range, t As Variant)
    '       param: x
    '       param: fx
    '       param: t    Value for which we need the interpolation (Can be a range)
 
    ' Sanity Check
    '===================================
 
    n = x.Rows.Count
    m = fx.Rows.Count
 
    If n <> m Then
        cubic_spline = "size(f(x)) != size(x)"
        GoTo out
    End If
 
    ' Creation of the equation system
    '===================================
   
    ' Matrix B
    '-----------------------------------
 
    Dim B() As Double
    ReDim B(n, 1)
 
    For i = 2 To n - 1
        B(i, 1) = ((fx(i + 1) - fx(i)) / (x(i + 1) - x(i)) - (fx(i) - fx(i - 1)) / (x(i) - x(i - 1))) * 6
    Next
 
    ' Matrix A
    '-----------------------------------
 
    Dim A() As Double
    ReDim A(n, n)
 
    A(1, 1) = 1
    A(n, n) = 1
 
    For i = 2 To n - 1
        A(i, i - 1) = (x(i) - x(i - 1))
        A(i, i + 1) = (x(i + 1) - x(i))
        A(i, i) = (A(i, i - 1) + A(i, i + 1)) * 2
    Next
 
    ' Solution: Compute Second Derivatives
    '-----------------------------------
 
    fxpp = Application.WorksheetFunction.MMult(Application.WorksheetFunction.MInverse(A), B)
 
    ' First Derivative f'
    Dim fxp() As Double
    ReDim fxp(n, 1)
 
    ' Third f'''
    Dim fxppp() As Double
    ReDim fxppp(n, 1)
 
    ' Solution: Compute first and third derivatives
    '-----------------------------------
 
    For i = 1 To n - 1
        fxp(i, 1) = (fx(i + 1, 1) - fx(i, 1)) / (x(i + 1) - x(i)) - (x(i + 1) - x(i)) * fxpp(i, 1) / 3 - (x(i + 1) - x(i)) * fxpp(i + 1, 1) / 6
        fxppp(i, 1) = (fxpp(i + 1, 1) - fxpp(i, 1)) / (x(i + 1) - x(i))
    Next
    
    ' if t is not a range then we may have a problem
    ' we cast any numeric value into an array of size 1
    '==================================
    
    Dim size As Integer
    
    If (VarType(t) = 5 Or VarType(t) = 4 Or VarType(t) = 2 Or VarType(t) = 3) Then
        size = 1
        Dim temp As Double
        temp = t
        
        ReDim t(1)
        t(1) = temp
    Else
        size = t.Rows.Count
    End If
 
    ' For each value compute the interpolated fx
    '==================================
    
    Dim target() As Double
    ReDim target(size, 1)
 
    For j = 1 To size
 
        ' find the function we need to use
        '-----------------------------------
 
        Dim idx As Integer
   
        idx = 1
   
        For i = 1 To n
       
            If (t(j) >= x(i)) Then
                idx = i
            End If
   
        Next
   
        If (t(j) >= x(n)) Then
            idx = n - 1
        End If
   
        Dim x1 As Double
        x1 = x(idx)
   
        ' Compute the interpolation
        target(j, 1) = fx(idx) + fxp(idx, 1) * (t(j) - x1) + fxpp(idx, 1) * (t(j) - x1) ^ 2 / 2 + fxppp(idx, 1) * (t(j) - x1) ^ 3 / 6
 
    Next
 
    cubic_spline = target
 
out:
End Function
